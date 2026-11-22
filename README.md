# Blood Circulation & Blockages Simulation

<p align="center">
  <img src="https://raw.githubusercontent.com/Joshua-Sarkar/Joshua-Sarkar/media/repositories/blood-circulation-simulation/hero.gif" width="100%" alt="Animated vascular graph simulation banner" />
</p>

<p align="center">
  <img src="https://raw.githubusercontent.com/Joshua-Sarkar/Joshua-Sarkar/media/repositories/blood-circulation-simulation/flow.gif" width="100%" alt="Animated graph-based blood cell simulation workflow" />
</p>

A small systems-programming experiment that represents a vascular network as a graph and moves simulated blood-cell objects through queues attached to each node. A lightweight C HTTP server exposes simulation controls to a browser page.

> **This is a data-structure simulation, not a physiological, diagnostic, or medical model.**

## Model

- **Vessel network:** nodes are connected through adjacency lists; each node stores capacity, current cell count and a queue.
- **Cell movement:** a simulation tick visits nodes, removes a cell from a non-blocked node, chooses one of its neighbours and attempts to enqueue the cell there.
- **Capacity rule:** if the destination is full, the cell is returned to its original queue.
- **Blockages:** a per-node countdown prevents movement through the selected node until the timer expires.
- **HTTP interface:** libmicrohttpd serves state and accepts tick/blockage requests; the browser visualiser calls those routes.

## Current API

The server in `api.c` listens on port `8888`.

| Method | Route | Current behaviour |
|---|---|---|
| GET | `/state` | Returns a JSON object containing cell counts by node |
| POST | `/tick` | Advances one simulation tick |
| POST | `/blockage` | Applies the example blockage to node 2 for 50 ticks |

The current blockage handler is hard-coded to node 2 and duration 50; it does not yet parse a configurable node or duration from the request.

## Code map

| File | Responsibility |
|---|---|
| `api.c` | HTTP server, five-node example graph, route handlers |
| `graph.h` | `VesselNode` / `VascularGraph` types and graph function declarations |
| `graph.c` | Currently duplicates the graph header declarations; graph function implementations are still needed |
| `queue.h`, `queue.c` | Linked queue for `BloodCell` pointers |
| `simulation.h`, `simulation.c` | Tick logic, capacity checks, blockage countdown and JSON state |
| `index.html`, `visualizer.js` | Buttons and browser-side API calls |

## Build status

The repository is an early prototype and is **not currently a complete, verified build**: `graph.c` contains header declarations rather than implementations for `create_graph`, `get_node_by_id`, `add_connection`, and `free_graph`. Those functions must be implemented before the backend can link successfully.

On Debian/Ubuntu, install the HTTP library:

```bash
sudo apt-get update
sudo apt-get install -y build-essential libmicrohttpd-dev
```

After implementing the missing graph functions in `graph.c`, compile from the repository root:

```bash
gcc -Wall -Wextra -std=c11 api.c graph.c queue.c simulation.c -lmicrohttpd -o vascular-sim
./vascular-sim
```

Open `index.html` in a browser after the server is running. The current JavaScript uses `http://localhost:8888`.

## Suggested next engineering steps

1. Implement graph allocation, adjacency management, capacity initialisation and safe cleanup.
2. Make blockage requests accept validated node IDs and durations.
3. Add cell seeding and stable cell IDs so movement can be observed over time.
4. Return structured JSON errors and add CORS if the page is hosted on a different origin.
5. Add tests for empty queues, full destinations, blocked nodes and memory cleanup.

---

<p align="center"><sub>A graph, a queue, a tick, and a blocked edge.</sub></p>
