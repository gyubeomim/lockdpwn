/********************************************************************************
** Form generated from reading UI file 'controlform_boolean.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLFORM_BOOLEAN_H
#define UI_CONTROLFORM_BOOLEAN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QRadioButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControlFormBoolean
{
public:
    QGridLayout *gridLayout;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QLabel *lblControlName;
    QRadioButton *rbEnable;
    QRadioButton *rbDisable;

    void setupUi(QWidget *ControlFormBoolean)
    {
        if (ControlFormBoolean->objectName().isEmpty())
            ControlFormBoolean->setObjectName(QString::fromUtf8("ControlFormBoolean"));
        ControlFormBoolean->resize(430, 90);
        ControlFormBoolean->setMinimumSize(QSize(430, 90));
        ControlFormBoolean->setMaximumSize(QSize(16777215, 90));
        gridLayout = new QGridLayout(ControlFormBoolean);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        frame = new QFrame(ControlFormBoolean);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        lblControlName = new QLabel(frame);
        lblControlName->setObjectName(QString::fromUtf8("lblControlName"));
        lblControlName->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lblControlName, 0, 0, 1, 2);

        rbEnable = new QRadioButton(frame);
        rbEnable->setObjectName(QString::fromUtf8("rbEnable"));
        rbEnable->setChecked(true);

        gridLayout_2->addWidget(rbEnable, 1, 0, 1, 1);

        rbDisable = new QRadioButton(frame);
        rbDisable->setObjectName(QString::fromUtf8("rbDisable"));

        gridLayout_2->addWidget(rbDisable, 1, 1, 1, 1);


        gridLayout->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(ControlFormBoolean);

        QMetaObject::connectSlotsByName(ControlFormBoolean);
    } // setupUi

    void retranslateUi(QWidget *ControlFormBoolean)
    {
        ControlFormBoolean->setWindowTitle(QApplication::translate("ControlFormBoolean", "Form", 0, QApplication::UnicodeUTF8));
        lblControlName->setText(QApplication::translate("ControlFormBoolean", "Control name", 0, QApplication::UnicodeUTF8));
        rbEnable->setText(QApplication::translate("ControlFormBoolean", "Enable", 0, QApplication::UnicodeUTF8));
        rbDisable->setText(QApplication::translate("ControlFormBoolean", "Disable", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ControlFormBoolean: public Ui_ControlFormBoolean {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLFORM_BOOLEAN_H
