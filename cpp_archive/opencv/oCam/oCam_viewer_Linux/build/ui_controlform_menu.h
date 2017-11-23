/********************************************************************************
** Form generated from reading UI file 'controlform_menu.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLFORM_MENU_H
#define UI_CONTROLFORM_MENU_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControlFormMenu
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QLabel *lblControlName;
    QComboBox *cbControls;

    void setupUi(QWidget *ControlFormMenu)
    {
        if (ControlFormMenu->objectName().isEmpty())
            ControlFormMenu->setObjectName(QString::fromUtf8("ControlFormMenu"));
        ControlFormMenu->resize(430, 90);
        ControlFormMenu->setMinimumSize(QSize(430, 90));
        ControlFormMenu->setMaximumSize(QSize(16777215, 90));
        verticalLayout = new QVBoxLayout(ControlFormMenu);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(ControlFormMenu);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        lblControlName = new QLabel(frame);
        lblControlName->setObjectName(QString::fromUtf8("lblControlName"));
        lblControlName->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lblControlName);

        cbControls = new QComboBox(frame);
        cbControls->setObjectName(QString::fromUtf8("cbControls"));

        verticalLayout_2->addWidget(cbControls);


        verticalLayout->addWidget(frame);


        retranslateUi(ControlFormMenu);

        QMetaObject::connectSlotsByName(ControlFormMenu);
    } // setupUi

    void retranslateUi(QWidget *ControlFormMenu)
    {
        ControlFormMenu->setWindowTitle(QApplication::translate("ControlFormMenu", "Form", 0, QApplication::UnicodeUTF8));
        lblControlName->setText(QApplication::translate("ControlFormMenu", "Control Name", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ControlFormMenu: public Ui_ControlFormMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLFORM_MENU_H
