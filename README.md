# Blood Circulation Simulation

## Overview
This project simulates blood flow through a vascular network represented as a graph. The core simulation engine is written in C for high performance and exposes RESTful API endpoints via a lightweight C web server.

## Components
- `graph.c`/`.h`: Defines the vessel graph and nodes.
- `queue.c`/`.h`: Implements the queue data structure for blood cells.
- `simulation.c`/`.h`: Contains simulation logic including flow rules and blockage.
- `api.c`: Runs a basic HTTP server using libmicrohttpd exposing REST API.
- `frontend/`: Contains HTML/JS visualization files.

## Build and Run
1. Install dependencies (`libmicrohttpd-dev` or equivalent).
2. Compile the backend:
