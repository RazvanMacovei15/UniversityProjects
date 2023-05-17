#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSlider>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QListWidget  *list_l;
    QListWidget  *list_r;
    QFormLayout* form_layout;
    QVBoxLayout* add_layout;
    QLabel* add_song_artist;
    QLabel* add_song_title;
    QLabel* add_song_Duration;
    QLabel* add_song_Link;
    QLabel* add_song_value_label;
    QLineEdit* add_song_artist_edit;
    QLineEdit* add_song_title_line_edit;
    QLineEdit* add_song_duration_edit;
    QLineEdit* add_song_link_edit;
    QSlider* add_song_value_slider;
    QPushButton* add_song_button;
    QPushButton* play_song_button;
    QPushButton* next_song_button;
    QPushButton* delete_song_button;
    QPushButton* update_song_button;
    QPushButton* sign_button;
    QPushButton* filter_song_button;
    QHBoxLayout* main_layout;
    QVBoxLayout* left_vertical_layout;
    QVBoxLayout* right_vertical_layout;
    QVBoxLayout* sign_layout;
    QGridLayout * grid;
    QGridLayout * grid_r;

    void add_song();
    void reload_list_data();
};
#endif MAINWINDOW_H
