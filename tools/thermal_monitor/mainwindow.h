/*
 * Thermal Monitor displays current temperature readings on a graph
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 3 or later, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QLabel>
#include <QMessageBox>
#include <QDesktopWidget>
#include <string>
#include <QVBoxLayout>
#include "qcustomplot/qcustomplot.h"
#include "thermaldinterface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void displayTemperature(QCustomPlot *customPlot);
    int addNewTemperatureSensor(QCustomPlot *customPlot, QString name);
    int addNewTemperatureTemperatureSample(int index, double temperature);
    bool getVisibleState(int index);

protected:
    virtual void closeEvent(QCloseEvent *event);

public slots:
    void currentChangedSlot(int index);
    void changePollIntervalSlot(uint new_val);
    void changeGraphVisibilitySlot(uint index, bool visible);
    void changeLogVariables(bool log_enabled, bool log_vis_only,
                        QString log_file_name);

private slots:
    void updateTemperatureDataSlot();
    void on_actionClear_triggered();
    void on_actionSet_Polling_Interval_triggered();
    void on_actionSensors_triggered();
    void on_actionLog_triggered();
    void on_action_About_triggered();
    void on_actionE_xit_triggered();

private:
    Ui::MainWindow *ui;
    QTimer tempUpdateTimer;
    QVector<QColor> colors;
    QVector<double> temp_samples;
    int currentTempsensorIndex;
    QVector<double> temperature_samples[MAX_TEMP_INPUT_COUNT];
    int current_sample_index[MAX_TEMP_INPUT_COUNT];
    uint temp_poll_interval;
    QString *sensor_name;
    bool *sensor_visibility;
    QLabel *sensor_label;
    QLabel *sensor_temp;
    QVector<QCPItemLine *> trips;

    QVBoxLayout *layout;
    QWidget *window;

    ThermaldInterface thermaldInterface;

    bool logging_enabled;
    bool log_visible_only;
    QString log_filename;
    QFile logging_file;
    QTextStream outStreamLogging;

    void resoreSettings();
    void storeSettings();
};

#endif // MAINWINDOW_H
