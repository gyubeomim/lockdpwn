/********************************************************************************
** Form generated from reading UI file 'controlform_integer.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLFORM_INTEGER_H
#define UI_CONTROLFORM_INTEGER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControlFormInteger
{
public:
    QGridLayout *gridLayout;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QLabel *lblControlName;
    QLabel *lblMin;
    QSpinBox *spnbxValue;
    QSlider *hsValue;
    QLabel *lblMax;

    void setupUi(QWidget *ControlFormInteger)
    {
        if (ControlFormInteger->objectName().isEmpty())
            ControlFormInteger->setObjectName(QString::fromUtf8("ControlFormInteger"));
        ControlFormInteger->resize(430, 90);
        ControlFormInteger->setMinimumSize(QSize(430, 90));
        ControlFormInteger->setMaximumSize(QSize(16777215, 90));
        gridLayout = new QGridLayout(ControlFormInteger);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        frame = new QFrame(ControlFormInteger);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        lblControlName = new QLabel(frame);
        lblControlName->setObjectName(QString::fromUtf8("lblControlName"));
        lblControlName->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lblControlName, 0, 0, 1, 3);

        lblMin = new QLabel(frame);
        lblMin->setObjectName(QString::fromUtf8("lblMin"));

        gridLayout_2->addWidget(lblMin, 1, 1, 1, 1);

        spnbxValue = new QSpinBox(frame);
        spnbxValue->setObjectName(QString::fromUtf8("spnbxValue"));
        spnbxValue->setMinimum(-99);

        gridLayout_2->addWidget(spnbxValue, 1, 0, 1, 1);

        hsValue = new QSlider(frame);
        hsValue->setObjectName(QString::fromUtf8("hsValue"));
        hsValue->setMinimum(-99);
        hsValue->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(hsValue, 1, 2, 1, 1);

        lblMax = new QLabel(frame);
        lblMax->setObjectName(QString::fromUtf8("lblMax"));

        gridLayout_2->addWidget(lblMax, 1, 3, 1, 1);


        gridLayout->addWidget(frame, 1, 0, 1, 1);


        retranslateUi(ControlFormInteger);
        QObject::connect(hsValue, SIGNAL(valueChanged(int)), spnbxValue, SLOT(setValue(int)));
        QObject::connect(spnbxValue, SIGNAL(valueChanged(int)), hsValue, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(ControlFormInteger);
    } // setupUi

    void retranslateUi(QWidget *ControlFormInteger)
    {
        ControlFormInteger->setWindowTitle(QApplication::translate("ControlFormInteger", "Form", 0, QApplication::UnicodeUTF8));
        lblControlName->setText(QApplication::translate("ControlFormInteger", "Control Name", 0, QApplication::UnicodeUTF8));
        lblMin->setText(QApplication::translate("ControlFormInteger", "Min", 0, QApplication::UnicodeUTF8));
        lblMax->setText(QApplication::translate("ControlFormInteger", "Max", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ControlFormInteger: public Ui_ControlFormInteger {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLFORM_INTEGER_H
