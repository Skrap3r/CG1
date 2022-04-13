

#include "CgQtGLRenderWidget.h"
#include "CgQtGui.h"
#include "CgQtMainApplication.h"
#include "../CgBase/CgEnums.h"
#include "../CgEvents/CgMouseEvent.h"
#include "../CgEvents/CgKeyEvent.h"
#include "../CgEvents/CgWindowResizeEvent.h"
#include "../CgEvents/CgLoadObjFileEvent.h"
#include "../CgEvents/CgTrackballEvent.h"
#include "../CgEvents/CgColorChangeEvent.h"
#include "../CgEvents/CgSchritteAusfuehrenEvent.h"
#include "../CgEvents/CgSchritteResetEvent.h"
#include "../CgEvents/CgRotationskoerperErstellenEvent.h"
#include "../CgEvents/CgRotationskoerperNormalenEvent.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QGroupBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QMenuBar>
#include <QActionGroup>
#include <QFileDialog>
#include <iostream>



CgQtGui::CgQtGui(CgQtMainApplication *mw)
    : m_mainWindow(mw)
{
    m_glRenderWidget = new CgQtGLRenderWidget;


    connect(m_glRenderWidget, SIGNAL(mouseEvent(QMouseEvent*)), this, SLOT(mouseEvent(QMouseEvent*)));
    connect(m_glRenderWidget, SIGNAL(viewportChanged(int,int)), this, SLOT(viewportChanged(int,int)));
    connect(m_glRenderWidget, SIGNAL(trackballChanged()), this, SLOT(slotTrackballChanged()));


    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;


    QWidget *opt = new QWidget;
    createOptionPanelExample1(opt);

    QWidget *otheropt = new QWidget;
    createOptionPanelExample2(otheropt);

    QWidget *uebung01opt = new QWidget;
    createOptionPanelUebung01(uebung01opt);

    QWidget *uebung02opt = new QWidget;
    createOptionPanelUebung02(uebung02opt);

    QTabWidget* m_tabs = new QTabWidget();
    m_tabs->addTab(uebung01opt, "&Uebung01");
    m_tabs->addTab(uebung02opt, "&Uebung02");
    m_tabs->addTab(opt,"&My Tab1");
    m_tabs->addTab(otheropt,"&My Tab2");
    container->addWidget(m_tabs);

    m_tabs->setMaximumWidth(400);

    container->addWidget(m_glRenderWidget);

    QWidget *w = new QWidget;
    w->setLayout(container);
    mainLayout->addWidget(w);

    setLayout(mainLayout);
    setWindowTitle(tr("Übung Computergrafik 1 -  SoSe 2021"));


    /* create Menu Bar */
    m_menuBar = new QMenuBar;
    QMenu *file_menu = new QMenu("&File" );
    file_menu->addAction("&Open Mesh Model", this, SLOT(slotLoadMeshFile()));
    // todo: Add Quit-Action
    m_menuBar->addMenu( file_menu );
    QMenu *settings_menu = new QMenu("&Setting" );
    QMenu *polygon_mode_menu = new QMenu("&Polygon Mode" );

    QAction* m_custom_rot=settings_menu->addAction("&Custom Rotations", m_glRenderWidget, SLOT(slotCustomRotation()));
    m_custom_rot->setCheckable(true);
    m_custom_rot->setChecked(false);

    QAction* m_lighting=settings_menu->addAction("&Lighting on", m_glRenderWidget, SLOT(slotLighting()));
    m_lighting->setCheckable(true);
    m_lighting->setChecked(false);


    QActionGroup* polygonmode_group = new QActionGroup(this);
    polygonmode_group->setExclusive(true);

    QAction* points=polygon_mode_menu->addAction("&Points", m_glRenderWidget, SLOT(slotPolygonPoints()));
    points->setCheckable(true);
    points->setChecked(false);


    QAction* wireframe=polygon_mode_menu->addAction("&Wireframe", m_glRenderWidget, SLOT(slotPolygonWireframe()));
    wireframe->setCheckable(true);
    wireframe->setChecked(true);

    QAction* filled=polygon_mode_menu->addAction("&Filled", m_glRenderWidget, SLOT(slotPolygonFilled()));
    filled->setCheckable(true);
    filled->setChecked(false);



    polygonmode_group->addAction(points);
    polygonmode_group->addAction(wireframe);
    polygonmode_group->addAction(filled);



    // todo: Add Quit-Action
    m_menuBar->addMenu( file_menu );
    m_menuBar->addMenu( settings_menu );
    m_menuBar->addMenu( polygon_mode_menu );


    m_mainWindow->setMenuBar(m_menuBar);



}

QSlider *CgQtGui::createSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

void CgQtGui::createOptionPanelUebung02(QWidget* parent)
{
    QVBoxLayout *tab4_control = new QVBoxLayout();

    //Label Schrittte
    QLabel *schritte_label = new QLabel("Anzahl der Schritte wählen:");
    tab4_control->addWidget(schritte_label);
    schritte_label->setAlignment(Qt::AlignCenter);

    //Spinbox Schritte
    mySpinBoxSchritte = new QSpinBox();
    tab4_control->addWidget(mySpinBoxSchritte);
    mySpinBoxSchritte->setMinimum(1);
    mySpinBoxSchritte->setMaximum(50);
    mySpinBoxSchritte->setValue(2);
    // mySpinBoxSchritte->setSuffix("   suffix");
    mySpinBoxSchritte->setPrefix("Schritte:  ");
    connect(mySpinBoxSchritte, SIGNAL(valueChanged(int) ), this, SLOT(slotMySpinBox1Changed()) );
    tab4_control->addWidget(mySpinBoxSchritte);

    //Button Ausführen
    QPushButton* myButtonAusfuehren = new QPushButton("&a) Ausfuehren");
    tab4_control->addWidget(myButtonAusfuehren);
    connect(myButtonAusfuehren, SIGNAL( clicked() ), this, SLOT(slotButtonSchritteAusfuehren()) );

    //Button Reset
    QPushButton* myButtonReset = new QPushButton("&b) Reset");
    tab4_control->addWidget(myButtonReset);
    connect(myButtonReset, SIGNAL( clicked() ), this, SLOT(slotButtonSchritteReset()) );

    //Label Schrittte
    QLabel *segmente_label = new QLabel("Anzahl der Rota. Segmente wählen:");
    tab4_control->addWidget(segmente_label);
    segmente_label->setAlignment(Qt::AlignCenter);



    //Spinbox Rotatorische Segmente
    mySpinBoxSegmente = new QSpinBox();
    tab4_control->addWidget(mySpinBoxSegmente);
    mySpinBoxSegmente->setMinimum(1);
    mySpinBoxSegmente->setMaximum(50);
    mySpinBoxSegmente->setValue(1);
    // mySpinBoxSegmente->setSuffix("   suffix");
    mySpinBoxSegmente->setPrefix("Segmente:  ");
    connect(mySpinBoxSegmente, SIGNAL(valueChanged(int) ), this, SLOT(slotMySpinBox1Changed()) );
    tab4_control->addWidget(mySpinBoxSegmente);

    //Button Erstellung des Rotationskörpers
    QPushButton* myButtonRotErstellen = new QPushButton("&C) Rotationskörper erstellen");
    tab4_control->addWidget(myButtonRotErstellen);
    connect(myButtonRotErstellen, SIGNAL( clicked() ), this, SLOT(slotButtonRotationskoerperErstellen()) );

    // Checkbox Normalen
    myCheckBoxNormalenZeichnen = new QCheckBox("d) Normalen zeichnen");
    myCheckBoxNormalenZeichnen->setCheckable(true);
    myCheckBoxNormalenZeichnen->setChecked(false);
    connect(myCheckBoxNormalenZeichnen, SIGNAL( clicked() ), this, SLOT(slotCheckboxNormalenZeichnenChanged()) );
    tab4_control->addWidget(myCheckBoxNormalenZeichnen);

    parent->setLayout(tab4_control);
}

void CgQtGui::slotCheckboxNormalenZeichnenChanged()
{
    CgBaseEvent* e = new CgRotationskoerperNormalenEvent(Cg::CgRotationskoerperNormalenEvent, myCheckBoxNormalenZeichnen->isChecked());
    notifyObserver(e);
    /*
    if (myCheckBoxNormalenZeichnen->isChecked())
    {
        std::cout << "Normalen gezeichnen" << std::endl;
    } else {
        std::cout << "Normalen gelöscht" << std::endl;
    }
    */
}

void CgQtGui::slotButtonRotationskoerperErstellen()
{
    CgBaseEvent* e = new CgRotationskoerperErstellenEvent(Cg::CgRotationskoerperErstellenEvent, mySpinBoxSegmente->value());
    notifyObserver(e);
    //std::cout << "Rotationskörper Erstellung gestartet, Anzahl Segmente: " << mySpinBoxSegmente->value() << std::endl;
}

void CgQtGui::slotButtonSchritteReset()
{
    CgBaseEvent* e = new CgSchritteResetEvent(Cg::CgSchritteResetEvent);
    notifyObserver(e);
    //std::cout << "Reset Schritte" << std::endl;
}

void CgQtGui::slotButtonSchritteAusfuehren()
{
    CgBaseEvent* e = new CgSchritteAusfuehrenEvent(Cg::CgSchritteAusfuehrenEvent,  mySpinBoxSchritte->value());
    notifyObserver(e);
    //std::cout << mySpinBoxRounds->value() << std::endl;
}

void CgQtGui::createOptionPanelUebung01(QWidget* parent)
{
    QVBoxLayout *tab3_control = new QVBoxLayout();

    //Label
    QLabel *options_label = new QLabel("Farbe nach RGB wählen: ");
    tab3_control->addWidget(options_label);
    options_label->setAlignment(Qt::AlignCenter);

    mySpinBoxRed = new QSpinBox();
    tab3_control->addWidget(mySpinBoxRed);
    mySpinBoxRed->setMinimum(0);
    mySpinBoxRed->setMaximum(255);
    mySpinBoxRed->setValue(255);
    mySpinBoxRed->setPrefix("Rotanteil:  ");
    connect(mySpinBoxRed, SIGNAL(valueChanged(int) ), this, SLOT(slotMySpinBox1Changed()) );

    mySpinBoxGreen = new QSpinBox();
    tab3_control->addWidget(mySpinBoxGreen);
    mySpinBoxGreen->setMinimum(0);
    mySpinBoxGreen->setMaximum(255);
    mySpinBoxGreen->setValue(255);
    mySpinBoxGreen->setPrefix("Grünanteil:  ");
    connect(mySpinBoxGreen, SIGNAL(valueChanged(int) ), this, SLOT(slotMySpinBox1Changed()) );

    mySpinBoxBlue = new QSpinBox();
    tab3_control->addWidget(mySpinBoxBlue);
    mySpinBoxBlue->setMinimum(0);
    mySpinBoxBlue->setMaximum(255);
    mySpinBoxBlue->setValue(255);
    mySpinBoxBlue->setPrefix("Blauanteil:  ");
    connect(mySpinBoxBlue, SIGNAL(valueChanged(int) ), this, SLOT(slotMySpinBox1Changed()) );

    QPushButton* myButtonChangedColor = new QPushButton("&Farbe Wechseln");
    tab3_control->addWidget(myButtonChangedColor);

    connect(myButtonChangedColor, SIGNAL( clicked() ), this, SLOT(slotMyButtonChangedColorPressed()) );

    parent->setLayout(tab3_control);
}

void CgQtGui::slotMyButtonChangedColorPressed()
{
    CgBaseEvent* e = new CgColorChangeEvent(Cg::CgColorChangeEvent, mySpinBoxRed->value(), mySpinBoxGreen->value(), mySpinBoxBlue->value());
    notifyObserver(e);
}

void CgQtGui::createOptionPanelExample1(QWidget* parent)
{
    QVBoxLayout *tab1_control = new QVBoxLayout();


    /*Example for using a label */

    QLabel *options_label = new QLabel("Options");
    tab1_control->addWidget(options_label);
    options_label->setAlignment(Qt::AlignCenter);


    /*Example for using a spinbox */

    mySpinBox1 = new QSpinBox();
    tab1_control->addWidget(mySpinBox1);
    mySpinBox1->setMinimum(1);
    mySpinBox1->setMaximum(50);
    mySpinBox1->setValue(3);
    // mySpinBox1->setSuffix("   suffix");
    // mySpinBox1->setPrefix("Prefix:  ");
    connect(mySpinBox1, SIGNAL(valueChanged(int) ), this, SLOT(slotMySpinBox1Changed()) );
    tab1_control->addWidget(mySpinBox1);


    /*Example for using a checkbox */

    myCheckBox1 = new QCheckBox("enable Option 1");
    myCheckBox1->setCheckable(true);
    myCheckBox1->setChecked(false);
    connect(myCheckBox1, SIGNAL( clicked() ), this, SLOT(slotMyCheckBox1Changed()) );
    tab1_control->addWidget(myCheckBox1);


    /*Example for using a button */

    QPushButton* myButton1 = new QPushButton("&drueck mich");
    tab1_control->addWidget(myButton1);

    connect(myButton1, SIGNAL( clicked() ), this, SLOT(slotMyButton1Pressed()) );

    parent->setLayout(tab1_control);

}

void CgQtGui::createOptionPanelExample2(QWidget* parent)
{
    QVBoxLayout *tab2_control = new QVBoxLayout();
    QHBoxLayout *subBox = new QHBoxLayout();



    /*Example for using a button group */

    QGroupBox* myGroupBox = new QGroupBox("Radiobutton Group Example ");

    myButtonGroup = new QButtonGroup(subBox);
    myButtonGroup->setExclusive(true);

    QRadioButton* radiobutton1 = new QRadioButton( "&Option1");
    QRadioButton* radiobutton2 = new QRadioButton( "&Option2");
    QRadioButton* radiobutton3 = new QRadioButton( "&Option3");
    QRadioButton* radiobutton4 = new QRadioButton( "&Option4");
    QRadioButton* radiobutton5 = new QRadioButton( "&Option5");

    radiobutton2->setChecked(true);

    myButtonGroup->addButton(radiobutton1,0);
    myButtonGroup->addButton(radiobutton2,1);
    myButtonGroup->addButton(radiobutton3,2);
    myButtonGroup->addButton(radiobutton4,3);
    myButtonGroup->addButton(radiobutton5,4);


    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radiobutton1);
    vbox->addWidget(radiobutton2);
    vbox->addWidget(radiobutton3);
    vbox->addWidget(radiobutton4);
    vbox->addWidget(radiobutton5);
    vbox->addStretch(1);
    myGroupBox->setLayout(vbox);
    subBox->addWidget(myGroupBox);
    tab2_control->addLayout(subBox);

    connect(myButtonGroup, SIGNAL( buttonClicked(int) ), this, SLOT( slotButtonGroupSelectionChanged() ) );
    parent->setLayout(tab2_control);
}





void CgQtGui::slotButtonGroupSelectionChanged()
{
    std::cout << "slotButtonGroupSelectionChanged" << std::endl;
}

void CgQtGui::slotMySpinBox1Changed()
{

}

void CgQtGui::slotMyCheckBox1Changed()
{

}


void CgQtGui::slotLoadMeshFile()
{



    QString file=  QFileDialog::getOpenFileName(this, tr("Open Obj-File"),"",tr("Model Files (*.obj)"));


    CgBaseEvent* e = new CgLoadObjFileEvent(Cg::LoadObjFileEvent, file.toStdString());

    notifyObserver(e);
}


void CgQtGui::slotTrackballChanged()
{
    CgBaseEvent* e = new CgTrackballEvent(Cg::CgTrackballEvent, m_glRenderWidget->getTrackballRotation());
    notifyObserver(e);
}

void CgQtGui::slotMyButton1Pressed()
{
    std::cout << "button 1 pressed " << std::endl;

}


void CgQtGui::mouseEvent(QMouseEvent* event)
{

    // std::cout << QApplication::keyboardModifiers() << std::endl;

    //  if(QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)==true)
    //    std::cout << Cg::ControlModifier << endl;


    if(event->type()==QEvent::MouseButtonPress)
    {


        CgBaseEvent* e = new CgMouseEvent(Cg::CgMouseButtonPress,
                                          glm::vec2(event->localPos().x() ,event->localPos().y()),
                                          (Cg::MouseButtons)event->button());

        notifyObserver(e);
    }

    if(event->type()==QEvent::MouseMove)
    {
        CgBaseEvent* e= new CgMouseEvent(Cg::CgMouseMove,
                                         glm::vec2(event->localPos().x() ,event->localPos().y()),
                                         (Cg::MouseButtons)event->button());
        notifyObserver(e);
    }



}

void CgQtGui::keyPressEvent(QKeyEvent *event)
{
    CgBaseEvent* e= new CgKeyEvent(Cg::CgKeyPressEvent,(Cg::Key)event->key(),(Cg::KeyboardModifiers)event->nativeModifiers(),event->text().toStdString());
    notifyObserver(e);
}


void CgQtGui::viewportChanged(int w, int h)
{
    CgBaseEvent* e = new CgWindowResizeEvent(Cg::WindowResizeEvent,w,h);
    notifyObserver(e);
}




CgBaseRenderer* CgQtGui::getRenderer()
{
    return m_glRenderWidget;
}





