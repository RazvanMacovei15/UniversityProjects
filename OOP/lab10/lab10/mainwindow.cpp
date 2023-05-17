#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QString>
#include <QListWidgetItem>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->main_layout = new QHBoxLayout{this->centralWidget()};
    this->left_vertical_layout = new QVBoxLayout{};
    this->right_vertical_layout = new QVBoxLayout{};
    this->list_l = new QListWidget{this->centralWidget()};
    this->list_r = new QListWidget{this->centralWidget()};

    this->main_layout->addLayout(this->left_vertical_layout);
    this->main_layout->addLayout(this->right_vertical_layout);

    this->left_vertical_layout->addWidget(this->list_l);
    this->right_vertical_layout->addWidget(this->list_r);

    this->form_layout = new QFormLayout{};
    this->add_layout = new QVBoxLayout{};
    this->add_layout->addLayout(this->form_layout);

    this->add_song_artist = new QLabel{"Artist :"};
    this->add_song_artist_edit = new QLineEdit{};
    this->add_song_title = new QLabel{"Title:"};
    this->add_song_title_line_edit = new QLineEdit{};
    this->add_song_Duration = new QLabel{"Duration:"};
    this->add_song_duration_edit = new QLineEdit{};
    this->add_song_Link = new QLabel{"Link:"};
    this->add_song_link_edit = new QLineEdit{};
    this->add_song_value_label = new QLabel{"song value:"};
    this->add_song_value_slider = new QSlider{};
    this->add_song_value_slider->setOrientation(Qt::Orientation::Horizontal);
    this->add_song_button = new QPushButton("Add");
    this->delete_song_button = new QPushButton("Delete");
    this->update_song_button = new QPushButton("Update");
    this->filter_song_button = new QPushButton("Filter");


    this->play_song_button = new QPushButton("Play");
    this->next_song_button = new QPushButton("Next");

    /*this->main_layout->addLayout(this->sign_layout);
    this->sign_button = new QPushButton(">");
    this->sign_layout->addWidget(sign_button);*/


    this->form_layout->addRow(this->add_song_title,this->add_song_title_line_edit);
    this->form_layout->addRow(this->add_song_artist,this->add_song_artist_edit);
    this->form_layout->addRow(this->add_song_Duration,this->add_song_duration_edit);
    this->form_layout->addRow(this->add_song_Link,this->add_song_link_edit);
    this->form_layout->addRow(this->add_song_value_label,this->add_song_value_slider);

    QGridLayout * grid = new QGridLayout{};
    grid->addWidget(add_song_button, 0, 0);
    grid->addWidget(delete_song_button, 0, 1);
    grid->addWidget(update_song_button, 0, 2);
    grid->addWidget(filter_song_button, 1, 1);

    QGridLayout * grid_r = new QGridLayout{};
    grid_r->addWidget(play_song_button, 0, 0);
    grid_r->addWidget(next_song_button, 0, 1);

    this->add_layout->addLayout(grid);
    this->right_vertical_layout->addLayout(grid_r);
    this->add_layout->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    this->left_vertical_layout->addLayout(this->add_layout);
    this->right_vertical_layout->addLayout(this->add_layout);

}

MainWindow::~MainWindow()
{
    delete ui;
}
