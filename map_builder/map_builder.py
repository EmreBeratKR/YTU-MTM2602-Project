import sys
from PyQt5.QtWidgets import QApplication, QWidget, QGridLayout, QPushButton, QSizePolicy, QVBoxLayout, QHBoxLayout, QFrame, QLabel, QMessageBox
from PyQt5.QtCore import Qt


SAVE_PATH = "map.txt"


class ButtonGrid(QWidget):
    def __init__(self):
        super().__init__()

        self.main = QVBoxLayout()
        self.top = QHBoxLayout()
        self.grid = QGridLayout()
        line = QFrame()
        line.setFrameShape(QFrame.HLine)
        line.setFrameShadow(QFrame.Sunken)
        self.main.addLayout(self.top)
        self.main.addWidget(line)
        self.main.addLayout(self.grid)
        self.setLayout(self.main)
        self.buttons = []
        self.rows = 3
        self.cols = 3
        self.brush = 0
        self.tile_images = ["plain.png", "hill.png", "wall.png"]
        self.tile_names = ["Plain", "Hill", "Wall"]
        self.tile_cost_texts = ["1", "5", "Inf"]
        self.map = {}

        self.import_save()

        self.create_grid()
        self.create_buttons()

    def create_grid(self):
        for button in self.buttons:
            button.deleteLater()
        self.buttons.clear()
        self.buttons_dict = {}

        for i in range(self.rows):
            for j in range(self.cols):
                button = QPushButton("")
                size_policy = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
                self.set_image(button, self.tile_images[0])
                button.setSizePolicy(size_policy)
                button.clicked.connect(lambda state, row=i, col=j: self.button_click(row, col, None))
                self.buttons_dict[(i, j)] = button
                try:
                    self.button_click(i, j, self.map[(i, j)])
                except:
                    self.button_click(i, j, 0)
                self.grid.addWidget(button, i, j)
                self.buttons.append(button)

    def create_buttons(self):
        top_left = QVBoxLayout()
        top_right = QVBoxLayout()
        top_right_layout = QHBoxLayout()
        top_left_buttons = QGridLayout()
        top_right_buttons = QGridLayout()
        line = QFrame()
        line.setFrameShape(QFrame.VLine)
        line.setFrameShadow(QFrame.Sunken)
        self.top.addLayout(top_left)
        self.top.addWidget(line)
        self.top.addLayout(top_right)
        self.top_left_title = QLabel("")
        self.top_left_title.setAlignment(Qt.AlignCenter)
        self.top_left_title.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)
        self.update_adjust_area_title()
        top_left.addWidget(self.top_left_title)
        top_left.addLayout(top_left_buttons)
        top_right_title = QLabel("<b>Select Tile Brush</b>")
        top_right_title.setAlignment(Qt.AlignCenter)
        top_right_title.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)
        top_right.addWidget(top_right_title)
        top_right.addLayout(top_right_layout)
        top_right_layout.addLayout(top_right_buttons)

        add_row_btn = QPushButton("Add Row")
        add_row_btn.clicked.connect(self.add_row)
        top_left_buttons.addWidget(add_row_btn, 0, 0)

        remove_row_btn = QPushButton("Remove Row")
        remove_row_btn.clicked.connect(self.remove_row)
        top_left_buttons.addWidget(remove_row_btn, 1, 0)

        add_col_btn = QPushButton("Add Column")
        add_col_btn.clicked.connect(self.add_column)
        top_left_buttons.addWidget(add_col_btn, 0, 1)

        remove_col_btn = QPushButton("Remove Column")
        remove_col_btn.clicked.connect(self.remove_column)
        top_left_buttons.addWidget(remove_col_btn, 1, 1)

        set_plain_tile_brush = QPushButton("Plain")
        set_plain_tile_brush.clicked.connect(lambda: self.on_click_tile_brush(0))
        top_right_buttons.addWidget(set_plain_tile_brush, 0, 2)

        set_hill_tile_brush = QPushButton("Hill")
        set_hill_tile_brush.clicked.connect(lambda: self.on_click_tile_brush(1))
        top_right_buttons.addWidget(set_hill_tile_brush, 1, 2)

        set_wall_tile_brush = QPushButton("Wall")
        set_wall_tile_brush.clicked.connect(lambda: self.on_click_tile_brush(2))
        top_right_buttons.addWidget(set_wall_tile_brush, 2, 2)

        export_button = QPushButton("Export Map")
        export_button.clicked.connect(self.export)
        export_layout = QHBoxLayout()
        export_layout.addWidget(export_button)
        top_left.addLayout(export_layout)

        self.preview = QLabel("Selected\nTile")
        self.preview.setAlignment(Qt.AlignCenter)
        self.set_image(self.preview, "hill.png")
        self.preview.setMinimumSize(80, 80)
        self.preview.setMaximumSize(80, 80)
        top_right_layout.addWidget(self.preview)
        self.on_click_tile_brush(0)

    def add_row(self):
        self.rows += 1
        self.create_grid()
        self.update_adjust_area_title()

    def remove_row(self):
        if self.rows > 1:
            self.rows -= 1
            self.create_grid()
        self.update_adjust_area_title()

    def add_column(self):
        self.cols += 1
        self.create_grid()
        self.update_adjust_area_title()

    def remove_column(self):
        if self.cols > 1:
            self.cols -= 1
            self.create_grid()
        self.update_adjust_area_title()

    def update_adjust_area_title(self):
        self.top_left_title.setText(f"<b>Adjust Map Size ({self.rows}, {self.cols})</b>")

    def on_click_tile_brush(self, tile_type):
        self.brush = tile_type
        self.set_image(self.preview, self.tile_images[tile_type])
        self.preview.setText(f"Selected\nTile:\n{self.tile_names[tile_type]}")

    def button_click(self, row, col, tile):
        brush = self.brush if tile is None else tile
        button = self.buttons_dict[(row, col)]
        button.setText(f"{self.tile_names[brush]}\nCost({self.tile_cost_texts[brush]})")
        self.set_image(button, self.tile_images[brush])
        self.map[(row, col)] = brush

    def set_image(self, widget, path):
        widget.setStyleSheet(f"background-image: url({path}); background-position: center;")

    def import_save(self):
        try:
            with open(SAVE_PATH, "r") as file:
                all = []
                for i, line in enumerate(file):
                    row = []
                    for c in line.split(","):
                        row.append(int(c))
                    all.append(row)
            for i in range(len(all)):
                for j in range(len(all[i])):
                    self.map[(i, j)] = all[i][j]
            self.rows = len(all)
            self.cols = len(all[0])
        except:
            print("Could not import the save!")

    def export(self):
        try:
            output = ""
            for i in range(self.rows):
                for j in range(self.cols):
                    try:
                        output += f"{self.map[(i, j)]}"
                        if j != self.cols - 1:
                            output += ","
                    except:
                        output += f"0,"
                output += "\n"
            with open(SAVE_PATH, "w") as file:
                file.write(output)
            msg = QMessageBox()
            msg.setIcon(QMessageBox.Information)
            msg.setText("Map is exported!")
            msg.setWindowTitle("Export Result")
            msg.setStandardButtons(QMessageBox.Ok)
            msg.exec_()
        except:
            msg = QMessageBox()
            msg.setIcon(QMessageBox.Critical)
            msg.setText("Failed to export map!")
            msg.setWindowTitle("Export Error")
            msg.setStandardButtons(QMessageBox.Ok)
            msg.exec_()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = ButtonGrid()
    window.setWindowTitle("Map Generator")
    window.resize(512, 512)
    window.show()
    sys.exit(app.exec_())
