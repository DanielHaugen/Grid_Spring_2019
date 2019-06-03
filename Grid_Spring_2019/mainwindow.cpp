#include "mainwindow.h"
#include "ui_mainwindow.h"

static QPushButton* recent_button; // The most recently clicked button. Useful for the ComboBox (Drop-Down Selector)
static QString Obj_String_Name; // The text value of the currently selected radio button
static QVector< QPair<QString, int> > obstaclePositions,
             naturalPositions,
             injuredPositions;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Setting the initial size of the window to that of the "un-expanded" version
    this->setFixedSize(QSize(685, 740));

    //Set the clicking of each button to its respective "Object Clicked" function
    connect(ui->pushButton_A1, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_A2, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_A3, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_A4, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_A5, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_A6, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_A7, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_A8, SIGNAL(released()),this,SLOT(digit_pressed()));

    connect(ui->pushButton_B1, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_B2, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_B3, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_B4, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_B5, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_B6, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_B7, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_B8, SIGNAL(released()),this,SLOT(digit_pressed()));

    connect(ui->pushButton_C1, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_C2, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_C3, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_C4, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_C5, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_C6, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_C7, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_C8, SIGNAL(released()),this,SLOT(digit_pressed()));

    connect(ui->pushButton_D1, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_D2, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_D3, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_D4, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_D5, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_D6, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_D7, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_D8, SIGNAL(released()),this,SLOT(digit_pressed()));

    //Initializing all of the radio buttons to their respecitve slots
    connect(ui->radioButton_Obstacles, SIGNAL(released()),this,SLOT(radio_pressed()));
    connect(ui->radioButton_Natural, SIGNAL(released()),this,SLOT(radio_pressed()));
    connect(ui->radioButton_Injured, SIGNAL(released()),this,SLOT(radio_pressed()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    QPushButton* button = static_cast<QPushButton*>(sender());
    recent_button = button;

    QString subString = button->objectName().right(2);

    if(subString != "A1" && subString != "A8" && subString != "D8")
    {
        ui->comboBox->setEnabled(true);

        //Check if any of the radio buttons are selected
        if(Obj_String_Name != "")
        {
            // Prevent the user from placing more than the limit of each item
            if( (Obj_String_Name == "Obstacle" && ui->label_Count_Obs->text() != "0") ||
                (Obj_String_Name == "Natural" && ui->label_Count_Nat->text() != "0")  ||
                (Obj_String_Name == "Injured" && ui->label_Count_Inj->text() != "0") )
            {
                adjust_Obj_Counts(true);
                recent_button->setText(Obj_String_Name);
                adjust_Obj_Counts(false);
            }
        }
    }
    else
        ui->comboBox->setEnabled(false);

    //Update the ComboBox (Drop-down selector)
    ui->comboBox->setItemText(0,button->text());
    ui->comboBox->setCurrentIndex(0);

    //Set the second part of the label to have the current position selected: [A,2]
    ui->label_Pos->setText(ui->label_Pos->text().left(20) +
                           subString.left(1) + ", " +
                           subString.right(1) + "]");
}

void MainWindow::on_comboBox_currentIndexChanged()
{
    QComboBox* combo = static_cast<QComboBox*>(sender());
    QPushButton* button = recent_button;

    // Prevent the user from placing more than the limit of each item
    if( (combo->currentText() == "Obstacle" && ui->label_Count_Obs->text() != "0") ||
        (combo->currentText() == "Natural" && ui->label_Count_Nat->text() != "0")  ||
        (combo->currentText() == "Injured" && ui->label_Count_Inj->text() != "0")  ||
         combo->currentText() == " " || combo->currentText() == "")
    {
        adjust_Obj_Counts(true);
        button->setText(combo->currentText());
        adjust_Obj_Counts(false);
    }
}

void MainWindow::on_pushButton_Clear_Radios_released()
{
    //Reset all the values of the radio buttons to their initial values
    ui->radioButton_Obstacles->setAutoExclusive(false);
    ui->radioButton_Natural->setAutoExclusive(false);
    ui->radioButton_Injured->setAutoExclusive(false);

    ui->radioButton_Obstacles->setChecked(false);
    ui->radioButton_Natural->setChecked(false);
    ui->radioButton_Injured->setChecked(false);

    ui->radioButton_Obstacles->setAutoExclusive(true);
    ui->radioButton_Natural->setAutoExclusive(true);
    ui->radioButton_Injured->setAutoExclusive(true);

    Obj_String_Name = "";
}


void MainWindow::radio_pressed()
{
    QRadioButton* radio = static_cast<QRadioButton*>(sender());

    //When a radio button is pressed, keep track of which one was last set
    Obj_String_Name = radio->text();
}

void MainWindow::adjust_Obj_Counts(bool isCheckAdd)
{
    QPushButton* button = recent_button;
    QString subString = button->objectName().right(2);

    QPair<QString, int> tmpPair;
    tmpPair.first = subString.left(1);
    tmpPair.second = subString.right(1).toInt();

    //If isCheckAdd is True, it will replenish the count of the type that was changed from
    //If isCheckAdd is False, it will decrease the count of the new type
    if(isCheckAdd)
    {   
        if(button->text() == "Obstacle")
        {
            //Update the Label count
            ui->label_Count_Obs->setText(QString::number(ui->label_Count_Obs->text().toInt()+1));
            //Remove the changed object type from its cooresponding QVector
            obstaclePositions.remove(obstaclePositions.indexOf(tmpPair));
        }
        else if(button->text() == "Natural")
        {
            ui->label_Count_Nat->setText(QString::number(ui->label_Count_Nat->text().toInt()+1));

            naturalPositions.remove(naturalPositions.indexOf(tmpPair));
        }
        else if(button->text() == "Injured")
        {
            ui->label_Count_Inj->setText(QString::number(ui->label_Count_Inj->text().toInt()+1));
            injuredPositions.remove(injuredPositions.indexOf(tmpPair));
        }
    }
    else
    {
        if(button->text() == "Obstacle")
        {
            //Update the Label count
            ui->label_Count_Obs->setText(QString::number(ui->label_Count_Obs->text().toInt()-1));
            //Update the QVector with the new position
            obstaclePositions.append(tmpPair);

        }
        else if(button->text() == "Natural")
        {
            ui->label_Count_Nat->setText(QString::number(ui->label_Count_Nat->text().toInt()-1));
            naturalPositions.append(tmpPair);
        }
        else if(button->text() == "Injured")
        {
            ui->label_Count_Inj->setText(QString::number(ui->label_Count_Inj->text().toInt()-1));
            injuredPositions.append(tmpPair);
        }
    }

    QString str = "";
    //Obstacle Positions
    for(int i = 0; i < obstaclePositions.size(); i++)
        str += "[" + obstaclePositions[i].first + ", " + QString::number(obstaclePositions[i].second) + "] ";

    ui->label_Coords_Obs->setText(str);

    str = "";
    //Natural Postions
    for(int i = 0; i < naturalPositions.size(); i++)
        str += "[" + naturalPositions[i].first + ", " + QString::number(naturalPositions[i].second) + "] ";

    ui->label_Coords_Nat->setText(str);

    str = "";
    //Injured Postions
    for(int i = 0; i < injuredPositions.size(); i++)
        str += "[" + injuredPositions[i].first + ", " + QString::number(injuredPositions[i].second) + "] ";

    ui->label_Coords_Inj->setText(str);
}

void MainWindow::on_pushButton_Clear_Grid_released()
{
    //Reset Everything related to the grid

    //Reset each of the object counts
    ui->label_Count_Obs->setText("3");
    ui->label_Count_Nat->setText("4");
    ui->label_Count_Inj->setText("3");

    //Reset all the buttons
    ui->pushButton_A2->setText(" ");
    ui->pushButton_A3->setText(" ");
    ui->pushButton_A4->setText(" ");
    ui->pushButton_A5->setText(" ");
    ui->pushButton_A6->setText(" ");
    ui->pushButton_A7->setText(" ");

    ui->pushButton_B1->setText(" ");
    ui->pushButton_B2->setText(" ");
    ui->pushButton_B3->setText(" ");
    ui->pushButton_B4->setText(" ");
    ui->pushButton_B5->setText(" ");
    ui->pushButton_B6->setText(" ");
    ui->pushButton_B7->setText(" ");
    ui->pushButton_B8->setText(" ");

    ui->pushButton_C1->setText(" ");
    ui->pushButton_C2->setText(" ");
    ui->pushButton_C3->setText(" ");
    ui->pushButton_C4->setText(" ");
    ui->pushButton_C5->setText(" ");
    ui->pushButton_C6->setText(" ");
    ui->pushButton_C7->setText(" ");
    ui->pushButton_C8->setText(" ");

    ui->pushButton_D1->setText(" ");
    ui->pushButton_D2->setText(" ");
    ui->pushButton_D3->setText(" ");
    ui->pushButton_D4->setText(" ");
    ui->pushButton_D5->setText(" ");
    ui->pushButton_D6->setText(" ");
    ui->pushButton_D7->setText(" ");

    //Reset the labels for the coordinates of the objects
    ui->label_Coords_Obs->setText(" ");
    ui->label_Coords_Nat->setText(" ");
    ui->label_Coords_Inj->setText(" ");
    ui->label_Pos->setText("Position Selected: [ , ]");

    //Remove all elements from the QVectors
    obstaclePositions.remove(0,obstaclePositions.size());
    naturalPositions.remove(0,naturalPositions.size());
    injuredPositions.remove(0,injuredPositions.size());

    //Reset the rest of the Global variables
    recent_button = {};
    ui->comboBox->setEnabled(false);
    ui->comboBox->setItemText(0,"Select Type-");
}

void MainWindow::on_pushButton_Expand_Collapse_released()
{
    if(this->width() != 1200)
    {
        this->setMaximumSize(QSize(1200, 740));
        this->resize(1200,this->height());
        ui->pushButton_Expand_Collapse->setText("Collapse");
        this->setFixedSize(QSize(1200, 740));
    }
    else
    {
        this->setMinimumSize(QSize(685, 740));
        this->resize(685,this->height());
        ui->pushButton_Expand_Collapse->setText("Expand");
        this->setFixedSize(QSize(685, 740));
    }
}
