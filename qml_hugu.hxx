#pragma once

#include <chrono>
#include <boost/range/algorithm/find.hpp>
#include <boost/range/algorithm/find_if.hpp>

#include <QtCore>
#include <QtDeclarative>

#include "usagi/sensors.hxx"

//class timer: public QTimer {
class qml_hugu: public QDeclarativeItem {
  Q_OBJECT
  Q_PROPERTY(double elapsed READ elapsed_getter NOTIFY elapsed_changed)
  Q_PROPERTY(double temperature READ temperature_getter NOTIFY temperature_changed)
  Q_PROPERTY(double temperature_critical READ temperature_critical_getter NOTIFY temperature_critical_changed)
  static const int interval = 10;
  double elapsed_;
  double temperature_;
  double temperature_critical_;
  std::chrono::high_resolution_clock::time_point last;
  usagi::sensors::sensors s;
//protected:
  void timerEvent(QTimerEvent*){
    update_sensors();
    auto now = std::chrono::high_resolution_clock::now();
    elapsed_ += std::chrono::duration_cast<std::chrono::duration<double>>(now - last).count();
    last = now;
  }
  void update_sensors(){
    auto chips = s();
    for(const auto& chip : chips){
      auto feature = boost::find_if(
        chip.features,
        [](const usagi::sensors::sensors::feature_type& f){
          return f.type == usagi::sensors::SENSORS_FEATURE_TEMP;
        }
      );
      if(feature != chip.features.end()){
        for(const auto& sf: feature->subfeatures)
          if(sf.name == feature->name + "_input")
            temperature_ = sf.value;
          else if(sf.name == feature->name + "_crit")
            temperature_critical_ = sf.value;
      }
    }
  }
public:
  explicit qml_hugu(QDeclarativeItem* p = nullptr)
    : QDeclarativeItem(p)
  {
    last = std::chrono::high_resolution_clock::now();
    startTimer(interval);
  }
  double elapsed_getter() const {
    return elapsed_;
  }
  double temperature_getter() const {
    return temperature_;
  }
  double temperature_critical_getter() const {
    return temperature_critical_;
  }
signals:
  void elapsed_changed();
  void temperature_changed();
  void temperature_critical_changed();
public slots:

};
