/********************************************************************************
** Form generated from reading UI file 'oCam_viewer.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OCAM_VIEWER_H
#define UI_OCAM_VIEWER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDockWidget>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QTabWidget>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_oCam
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QScrollArea *frmImage;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_5;
    QLabel *lblImage;
    QFrame *frame;
    QGridLayout *gridLayout_6;
    QComboBox *cbbDeviceList;
    QLabel *label;
    QToolButton *tbtnDevRefresh;
    QPushButton *btnStart;
    QDockWidget *dockControls;
    QWidget *dockWidgetContents_3;
    QGridLayout *gridLayout_7;
    QTabWidget *twController;
    QWidget *tabFormats;
    QGridLayout *gridLayout_3;
    QFrame *frmTabFormat;
    QGridLayout *gridLayout_4;
    QWidget *tabControls;
    QGridLayout *gridLayout_2;
    QScrollArea *scrControllerArea;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *vLayoutControls;

    void setupUi(QMainWindow *oCam)
    {
        if (oCam->objectName().isEmpty())
            oCam->setObjectName(QString::fromUtf8("oCam"));
        oCam->resize(1024, 752);
        QIcon icon;
        icon.addFile(QString::fromUtf8("resources/_withrobot.ico"), QSize(), QIcon::Normal, QIcon::Off);
        oCam->setWindowIcon(icon);
        oCam->setStyleSheet(QString::fromUtf8("QMainWindow::separator {\n"
"    background: black;\n"
"    width: 3px; /* when vertical */\n"
"    height: 3px; /* when horizontal */\n"
"}\n"
"\n"
"QMainWindow::separator:hover {\n"
"    background: red;\n"
"}"));
        oCam->setDocumentMode(false);
        oCam->setDockNestingEnabled(true);
        centralWidget = new QWidget(oCam);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        frmImage = new QScrollArea(centralWidget);
        frmImage->setObjectName(QString::fromUtf8("frmImage"));
        frmImage->setBaseSize(QSize(320, 240));
        frmImage->viewport()->setProperty("cursor", QVariant(QCursor(Qt::ArrowCursor)));
        frmImage->setMouseTracking(false);
        frmImage->setFrameShape(QFrame::Box);
        frmImage->setFrameShadow(QFrame::Plain);
        frmImage->setLineWidth(3);
        frmImage->setWidgetResizable(true);
        frmImage->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 477, 612));
        gridLayout_5 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        lblImage = new QLabel(scrollAreaWidgetContents);
        lblImage->setObjectName(QString::fromUtf8("lblImage"));
        lblImage->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(lblImage, 1, 0, 1, 1);

        frmImage->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(frmImage, 2, 0, 1, 2);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_6 = new QGridLayout(frame);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        cbbDeviceList = new QComboBox(frame);
        cbbDeviceList->setObjectName(QString::fromUtf8("cbbDeviceList"));
        cbbDeviceList->setStyleSheet(QString::fromUtf8(""));

        gridLayout_6->addWidget(cbbDeviceList, 1, 0, 1, 1);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label, 0, 0, 1, 2);

        tbtnDevRefresh = new QToolButton(frame);
        tbtnDevRefresh->setObjectName(QString::fromUtf8("tbtnDevRefresh"));

        gridLayout_6->addWidget(tbtnDevRefresh, 1, 1, 1, 1);

        btnStart = new QPushButton(frame);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #8f8f91;\n"
"    border-radius: 6px;\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #f6f7fa, stop: 1 #dadbde);\n"
"    min-width: 80px;\n"
"	min-height:30px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
"}\n"
"\n"
"QPushButton:flat {\n"
"    border: none; /* no border for a flat push button */\n"
"}\n"
"\n"
"QPushButton:default {\n"
"    border-color: navy; /* make the default button prominent */\n"
"}\n"
"\n"
""));

        gridLayout_6->addWidget(btnStart, 2, 0, 1, 2);


        gridLayout->addWidget(frame, 1, 0, 1, 2);

        oCam->setCentralWidget(centralWidget);
        dockControls = new QDockWidget(oCam);
        dockControls->setObjectName(QString::fromUtf8("dockControls"));
        dockControls->setEnabled(true);
        dockControls->setWindowIcon(icon);
        dockControls->setStyleSheet(QString::fromUtf8("QDockWidget {\n"
"    border: 1px solid lightgray;\n"
"    titlebar-close-icon: url(close.png);\n"
"    titlebar-normal-icon: url(float.png);\n"
"}\n"
"\n"
"QDockWidget::title {\n"
"    text-align: left;\n"
"    background: lightgray;\n"
"    padding-left: 35px;\n"
"}\n"
"\n"
"QDockWidget::close-button, QDockWidget::float-button {\n"
"    background: darkgray;\n"
"    padding: 0px;\n"
"    icon-size: 14px; /* maximum icon size */\n"
"}\n"
"\n"
"QDockWidget::close-button:hover, QDockWidget::float-button:hover {\n"
"    background: gray;\n"
"}\n"
"\n"
"QDockWidget::close-button:pressed, QDockWidget::float-button:pressed {\n"
"    padding: 1px -1px -1px 1px;\n"
"}\n"
"\n"
"QDockWidget::close-button {\n"
"    subcontrol-position: top left;\n"
"    subcontrol-origin: margin;\n"
"    position: absolute;\n"
"    top: 0px; left: 0px; bottom: 0px;\n"
"    width: 14px;\n"
"}\n"
"\n"
"QDockWidget::float-button {\n"
"    subcontrol-position: top left;\n"
"    subcontrol-origin: margin;\n"
"    position: absolute;\n"
"    "
                        "top: 0px; left: 16px; bottom: 0px;\n"
"    width: 14px;\n"
"}"));
        dockControls->setFloating(false);
        dockControls->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QString::fromUtf8("dockWidgetContents_3"));
        gridLayout_7 = new QGridLayout(dockWidgetContents_3);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        twController = new QTabWidget(dockWidgetContents_3);
        twController->setObjectName(QString::fromUtf8("twController"));
        twController->setMinimumSize(QSize(500, 240));
        twController->setMaximumSize(QSize(16777215, 16777215));
        twController->setAutoFillBackground(true);
        twController->setStyleSheet(QString::fromUtf8("QTabWidget::pane { /* The tab widget frame */\n"
"    border-top: 2px solid #C2C7CB;\n"
"}\n"
"\n"
"QTabWidget::tab-bar {\n"
"    left: 5px; /* move to the right by 5px */\n"
"}\n"
"\n"
"/* Style the tab using the tab sub-control. Note that\n"
"    it reads QTabBar _not_ QTabWidget */\n"
"QTabBar::tab {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,\n"
"                                stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);\n"
"    border: 2px solid #C4C4C3;\n"
"    border-bottom-color: #C2C7CB; /* same as the pane color */\n"
"    border-top-left-radius: 4px;\n"
"    border-top-right-radius: 4px;\n"
"    min-width: 8ex;\n"
"    padding: 2px;\n"
"}\n"
"\n"
"QTabBar::tab:selected, QTabBar::tab:hover {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #fafafa, stop: 0.4 #f4f4f4,\n"
"                                stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);\n"
"}\n"
"\n"
"Q"
                        "TabBar::tab:selected {\n"
"    border-color: #9B9B9B;\n"
"    border-bottom-color: #C2C7CB; /* same as pane color */\n"
"}\n"
"\n"
"QTabBar::tab:!selected {\n"
"    margin-top: 2px; /* make non-selected tabs look smaller */\n"
"}"));
        twController->setTabShape(QTabWidget::Rounded);
        twController->setElideMode(Qt::ElideNone);
        twController->setDocumentMode(false);
        twController->setTabsClosable(false);
        twController->setMovable(false);
        tabFormats = new QWidget();
        tabFormats->setObjectName(QString::fromUtf8("tabFormats"));
        gridLayout_3 = new QGridLayout(tabFormats);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        frmTabFormat = new QFrame(tabFormats);
        frmTabFormat->setObjectName(QString::fromUtf8("frmTabFormat"));
        frmTabFormat->setMinimumSize(QSize(480, 0));
        frmTabFormat->setMaximumSize(QSize(16777215, 16777215));
        frmTabFormat->setFrameShape(QFrame::StyledPanel);
        frmTabFormat->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frmTabFormat);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));

        gridLayout_3->addWidget(frmTabFormat, 0, 0, 1, 1);

        twController->addTab(tabFormats, QString());
        tabControls = new QWidget();
        tabControls->setObjectName(QString::fromUtf8("tabControls"));
        gridLayout_2 = new QGridLayout(tabControls);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        scrControllerArea = new QScrollArea(tabControls);
        scrControllerArea->setObjectName(QString::fromUtf8("scrControllerArea"));
        scrControllerArea->setMinimumSize(QSize(480, 200));
        scrControllerArea->setMaximumSize(QSize(16777215, 16777215));
        scrControllerArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 482, 668));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        vLayoutControls = new QVBoxLayout();
        vLayoutControls->setSpacing(6);
        vLayoutControls->setObjectName(QString::fromUtf8("vLayoutControls"));

        verticalLayout_2->addLayout(vLayoutControls);

        scrControllerArea->setWidget(scrollAreaWidgetContents_2);

        gridLayout_2->addWidget(scrControllerArea, 0, 0, 1, 1);

        twController->addTab(tabControls, QString());

        gridLayout_7->addWidget(twController, 0, 0, 1, 1);

        dockControls->setWidget(dockWidgetContents_3);
        oCam->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockControls);

        retranslateUi(oCam);

        twController->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(oCam);
    } // setupUi

    void retranslateUi(QMainWindow *oCam)
    {
        oCam->setWindowTitle(QApplication::translate("oCam", "oCam Viewer", 0, QApplication::UnicodeUTF8));
        lblImage->setText(QApplication::translate("oCam", "oCam", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("oCam", "Device", 0, QApplication::UnicodeUTF8));
        tbtnDevRefresh->setText(QApplication::translate("oCam", "Refresh", 0, QApplication::UnicodeUTF8));
        btnStart->setText(QApplication::translate("oCam", "Connect", 0, QApplication::UnicodeUTF8));
        twController->setTabText(twController->indexOf(tabFormats), QApplication::translate("oCam", "Formats", 0, QApplication::UnicodeUTF8));
        twController->setTabText(twController->indexOf(tabControls), QApplication::translate("oCam", "Controls", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class oCam: public Ui_oCam {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OCAM_VIEWER_H
