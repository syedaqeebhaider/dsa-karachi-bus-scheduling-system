# Karachi Bus Scheduling and Tracking System

A C++ console-based system that models Karachi's public bus network as a graph and applies multiple data structures to automate ticket booking, route management, seat tracking, and revenue reporting — built for a Data Structures & Algorithms course project at Bahria University.

## 📌 Overview

Public transportation management is often handled manually — leading to booking errors, poor seat tracking, and inefficient route monitoring. This project automates those operations end-to-end: passengers can view routes, book normal or priority tickets, and receive a ticket slip; administrators can process bookings, update route locations, monitor seats, and generate revenue reports.

The project demonstrates how multiple data structures work together to solve a real, practical scheduling problem rather than being used in isolation.

## 🗺️ Route Network

The bus network covers 5 routes across major Karachi hubs, modeled as a connected graph — stops are nodes, and distances (in km) are weighted edges. Several stops (e.g. Nagan Chowrangi, Korangi, Nipa/Tower) act as shared intersections connecting multiple routes.

![Full Bus Network Route Map](./Graphs/Main%20graph%20with%20coordinates.jpeg)

Each individual route, with its stop sequence and distances:

| Route | Bus ID | Seats | Path |
|-------|--------|-------|------|
| R1 | 101 | 40 | Model Colony → Malir Halt → Drigh Road → Karsaz → Nursery → Tower |
| R3 | 102 | 35 | Power House → Nagan Chowrangi → Sakhi Hasan → KDA Chowrangi → Liaquatabad |
| R2 | 103 | 40 | New Karachi → Nagan Chowrangi → Shafiq Mor → Sohrab Goth → Gulshan → Nipa → Johar Mor → Korangi |
| R10 | 104 | 30 | Numaish → Korangi → Shah Faisal → Ibrahim Hyderi |
| R9 | 105 | 25 | Tower → Banaras → Orangi |

![Network Route Highlights Korangi As A Source](./Graphs/Korangi%20as%20source.jpeg)
![Network Route Highlights Nagin As A Source](./Graphs/Nagin%20as%20source.jpeg)
![Network Route Highlights Tower As A Source](./Graphs/Tower%20as%20source.jpeg)


## 🧠 Data Structures & Algorithms Used

| Structure | Used For | Why |
|-----------|----------|-----|
| **Arrays** | Storing bus records (ID, route, stops, seats, status) | Fixed number of buses, needs direct/indexed access |
| **Queue (FIFO)** | Normal ticket booking | Processes booking requests fairly, in the order received |
| **Max-Heap (Priority Queue)** | Priority ticket booking | Urgent/priority passengers get processed ahead of normal ones |
| **Binary Search Tree (BST)** | Route storage & lookup | Efficient route insertion and search by route ID |
| **Stack** | Route location history | Tracks previous locations, supports undo on location updates |

## 🚀 Features

**Passenger Panel**
- Book a normal ticket (Rs. 100) — added to the FIFO booking queue
- Book a priority ticket (Rs. 150) — added to the max-heap by priority
- View current booking queue / priority bookings
- View all routes and live seat availability
- Auto-generated ticket slip with ticket ID, route path, and fare

**Admin Panel** *(authenticated)*
- Process normal and priority bookings (assigns seats, updates revenue)
- Update a route's current location (with stack-based undo support)
- Search a route by ID (BST lookup)
- View all routes, available seats, and a full revenue report (normal vs. priority tickets, total revenue)

## 🛠️ Built With

- **C++** — no external libraries, standard console I/O only

## 📄 Report

A full project report is included, covering the problem statement, literature review, methodology, and detailed explanation of each data structure's role — see `DSA.Project.Report.docx` detailed Report in repo.

## 🎓 What This Project Demonstrates

- Combining multiple data structures (array, queue, heap, BST, stack) in one working system rather than using each in isolation
- Modeling a real-world transportation network as a graph-like route structure
- Applying FIFO vs. priority-based processing to a practical booking scenario
- Basic authentication and role-based access (passenger vs. admin) in a console application

## 🔮 Future Improvements

- Database integration for persistent storage
- GPS-based live tracking
- Web-based interface
- Mobile application support

## 👥 Contributors

Group project — Department of Computer Science, Bahria University, Karachi Campus
**My contribution:** ticket data structures, circular queue and max-heap implementation, and related booking functions.
