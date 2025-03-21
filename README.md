# Emergency_Safety_Vest

This is the project titled *'Emergency Safety Vest'* by *Pranav Kumar, Nagalakshmi Jhanavi, N. Meghnana, Rohith Vinayak, D. Nithin, Ginka Varshith, Dhanasari Ambadi, Dharani, J. Annop, Naga Gopi Krishna*. Under the mentorship of *Tanmay Sugandhi*
This is a record of the project work carried out by us during the year *2024-2025* as part of *INDUCTION* under the guidance and supervision of *Mr. G. Kovidh Addhish & Mr. Aarushraj Puduchery* (Technical Heads) and *Mr. N.V.V.S. Narayana* (The President of THE ROBOTICS CLUB).

## Abstract
During emergency situations like natural disasters, emergency personnel must worry about their safety as well as the people they are trying to aid. However, the current methods to monitor emergency responders are insufficient. We might not be able to track the responder’s location or vitals when they are busy helping others.

The **Emergency Safety Vest** is a combination of a vest and a helmet designed to monitor all vital parameters of emergency responders in real-time. It can measure **heart rate, body temperature, SpO2 levels, location, and the presence of harmful gases**. We use the **MAX30102 sensor** for monitoring heart rate and SpO2, while an **ESP32 microcontroller** controls the sensors and transmits data to the **Blynk App**. If any serious health changes occur or the personnel gets lost, their location can be tracked. The helmet also features an **ESP32-CAM module** mounted on **SG90 servo motors**, allowing real-time **video streaming and 360-degree environmental monitoring**.

## Introduction
During emergencies, responders need to ensure their safety while helping others. However, traditional monitoring methods fail to provide **real-time insights into responders' vitals and surroundings**. Our **Emergency Safety Vest** solves this issue by integrating **IoT-based health monitoring** and **real-time tracking**.

## Problem Statement
Emergency personnel often work in hazardous environments, facing risks such as toxic gas exposure and extreme physical strain. Current monitoring solutions are **inadequate** as they do not provide **real-time health tracking and location data**. Our **Emergency Safety Vest** aims to bridge this gap with a **wearable IoT-enabled system**.

## Features
- **Real-Time Health Monitoring:** Measures **heart rate, SpO2, and body temperature**.
- **Location Tracking:** Uses **NEO-6M GPS module** to track the wearer's exact position.
- **Gas Detection:** Equipped with an **MQ-7 gas sensor** to detect harmful gases.
- **360-Degree Video Streaming:** The **ESP32-CAM module** streams video for remote monitoring.
- **Wireless Data Transmission:** Uses **Wi-Fi and the Blynk App** for real-time alerts and monitoring.
- **Compact & Wearable:** The vest and helmet ensure ease of use without interfering with movement.

## Images of the Vest


## Working Video


## Block Diagram


## Circuit Diagram


## CAD Design


## Working Mechanism
    i. The **ESP32 microcontroller** connects to Wi-Fi and transmits real-time data.
    ii. **Sensors** (MAX30102, DHT11, MQ-7) collect vital health and environmental data.
    iii. The **GPS module** continuously updates the responder’s location.
    iv. **ESP32-CAM** captures live video footage, which is streamed to the monitoring app.
    v. If a **dangerous change** in vitals is detected, an **alert is sent** via the Blynk App.
    vi. If toxic gases are detected, the system alerts the operator.

## Source Code
Check the file in this repository.

## Component List
Check the file in this repository.

## Future Enhancements
    i. Upgrade the **GPS module** for **higher accuracy**.
    ii. Improve the **placement of components** for better comfort.
    iii. Integrate a **GPRS/GSM module** for **better connectivity**.
    iv. Enhance battery life for prolonged field use.
    v. Add **AI-powered anomaly detection** for better safety insights.

