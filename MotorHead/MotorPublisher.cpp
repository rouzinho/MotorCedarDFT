/*======================================================================================================================

    Copyright 2011, 2012, 2013, 2014, 2015 Institut fuer Neuroinformatik, Ruhr-Universitaet Bochum, Germany

    This file is part of cedar.

    cedar is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    cedar is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
    License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with cedar. If not, see <http://www.gnu.org/licenses/>.

========================================================================================================================

    Institute:   Ruhr-Universitaet Bochum
                 Institut fuer Neuroinformatik

    File:        EarSubscriber.h

    Maintainer:  Tutorial Writer Person
    Email:       cedar@ini.rub.de
    Date:        2011 12 09

    Description:

    Credits:

======================================================================================================================*/

// CEDAR INCLUDES
#include "MotorPublisher.h"
#include <cedar/processing/ExternalData.h> // getInputSlot() returns ExternalData
#include <cedar/auxiliaries/MatData.h> // this is the class MatData, used internally in this step
#include "cedar/auxiliaries/math/functions.h"
#include <cmath>
#include "std_msgs/Float64.h"


// SYSTEM INCLUDES

//----------------------------------------------------------------------------------------------------------------------
// constructors and destructor
//----------------------------------------------------------------------------------------------------------------------
MotorPublisher::MotorPublisher()
:
cedar::proc::Step(true),
mTopic(new cedar::aux::StringParameter(this, "Topic Name", "")),
//mOutput(new cedar::aux::MatData(cv::Mat::zeros(50, 50, CV_32F))),
mCenter(new cedar::aux::DoubleParameter(this,"Motor Pos",25))
{
this->declareInput("motor", true);
motorPos.data = 0;
this->connect(this->mCenter.get(), SIGNAL(valueChanged()), this, SLOT(reCompute()));
this->connect(this->mTopic.get(), SIGNAL(valueChanged()), this, SLOT(reName()));
}
//----------------------------------------------------------------------------------------------------------------------
// methods
//----------------------------------------------------------------------------------------------------------------------
void MotorPublisher::compute(const cedar::proc::Arguments&)
{

  cedar::aux::ConstDataPtr op1 = this->getInputSlot("motor")->getData();
  cv::Mat doublepos = op1->getData<cv::Mat>();

  ros::Rate loop_rate(98);
  float t1 = doublepos.at<float>(0);
  pos = static_cast<double> (t1);
  if(std::abs(old_pos - pos) < 0.005)
  {
    pub.publish(motorPos);
    loop_rate.sleep();
    ros::spinOnce();
  }

  motorPos.data = pos;
  old_pos = pos;

}

void MotorPublisher::reCompute()
{
   const std::string tname = topicName;
   pub = n.advertise<std_msgs::Float64>(tname, 1000);
}

void MotorPublisher::reName()
{
   topicName = this->mTopic->getValue();
}

void MotorPublisher::reset()
{

	//ros::shutdown();

}
