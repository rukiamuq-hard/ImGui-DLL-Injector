# Extremy Injector

**Minimal C++ Injector with GUI based on Dear ImGui**
**and use based WinAPI functionality**


![Image of Injector](/img/imgui.png "This is a sample image.")

### Tech Stack
* **Graphics:** OpenGL3
* **Window/Input:** GLFW3
* **GL Loader:** GLAD
* **Interface:** Dear ImGui

### Dependencies
Required for building:
* `imgui` (core and backends for glfw/opengl3)
* `glfw3`
* `glad`

### Downsides and Flaws
* **Manual Input:** Requires manual entry of the Process ID (PID); no "attach by name" feature.
* **Path Dependency:** DLL path must be provided manually.
* **Stability:** Minimal validation of handles and target process states.

### License
This project uses Dear ImGui (MIT License).

**Donate![DonatikUA](https://rukiamuq.donatik.ua)**
