/********************************************************************************
** Form generated from reading UI file 'format_tree_form.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMAT_TREE_FORM_H
#define UI_FORMAT_TREE_FORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormatTreeForm
{
public:
    QGridLayout *gridLayout;
    QTreeWidget *treeFormat;
    QPushButton *btnApply;

    void setupUi(QWidget *FormatTreeForm)
    {
        if (FormatTreeForm->objectName().isEmpty())
            FormatTreeForm->setObjectName(QString::fromUtf8("FormatTreeForm"));
        FormatTreeForm->resize(430, 400);
        FormatTreeForm->setMinimumSize(QSize(430, 120));
        FormatTreeForm->setMaximumSize(QSize(16777215, 16777215));
        gridLayout = new QGridLayout(FormatTreeForm);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        treeFormat = new QTreeWidget(FormatTreeForm);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeFormat->setHeaderItem(__qtreewidgetitem);
        treeFormat->setObjectName(QString::fromUtf8("treeFormat"));
        treeFormat->setProperty("showDropIndicator", QVariant(false));

        gridLayout->addWidget(treeFormat, 0, 0, 1, 1);

        btnApply = new QPushButton(FormatTreeForm);
        btnApply->setObjectName(QString::fromUtf8("btnApply"));

        gridLayout->addWidget(btnApply, 1, 0, 1, 1);


        retranslateUi(FormatTreeForm);

        QMetaObject::connectSlotsByName(FormatTreeForm);
    } // setupUi

    void retranslateUi(QWidget *FormatTreeForm)
    {
        FormatTreeForm->setWindowTitle(QApplication::translate("FormatTreeForm", "Form", 0, QApplication::UnicodeUTF8));
        btnApply->setText(QApplication::translate("FormatTreeForm", "Apply", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FormatTreeForm: public Ui_FormatTreeForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMAT_TREE_FORM_H
