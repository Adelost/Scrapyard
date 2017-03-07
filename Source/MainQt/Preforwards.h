#pragma once

/*
    Forward declarations useful in header files.
    Only classes not usually changed should be
    put here, similar to precompiled headers.
*/

// Useful utilities

#include <memory> // unique_ptr, shared_ptr
using std::shared_ptr;
using std::unique_ptr;

// Project related

class RenderWidget;

// Qt related

class QTimer;
class QAction;
class QBoxLayout;
class QCheckBox;
class QColorDialog;
class QComboBox;
class QDir;
class QDockWidget;
class QDoubleSpinBox;
class QFileDialog;
class QGraphicsBlurEffect;
class QLabel;
class QListWidget;
class QMainWindow;
class QMenu;
class QMessageBox;
class QPlainTextEdit;
class QPushButton;
class QPushButton;
class QScrollArea;
class QShortcut;
class QSignalMapper;
class QSplitter;
class QStandardItemModel;
class QString;
class QTextStream;
class QTimer;
class QTreeView;