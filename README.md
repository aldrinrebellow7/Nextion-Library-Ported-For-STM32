# 📟 Nextion Library Ported for STM32

A lightweight and efficient port of the popular **ITEAD Nextion Display Library**, tailored for **STM32 microcontrollers** using **HAL drivers** and **C++ support**. This library simplifies serial communication between STM32 and Nextion HMI displays, enabling seamless GUI integration in embedded systems.

---

## 🚀 Features

- 🔌 **UART-based communication** via STM32 HAL
- 🧾 Control **pages, text fields, buttons, variables** and more
- 🔁 Simple API to send/receive Nextion commands
- 💡 Designed for **STM32CubeIDE with C++ enabled**
- ⚡ Compatible with STM32F1, F4, and other STM32 families

> ⚠️ **Note**: This library is written in **C++**. Make sure your STM32 project is configured to support C++ (`.cpp` files, proper C++ toolchain, and `extern "C"` where needed for HAL compatibility).

---

## 🧰 Getting Started

### ✅ Prerequisites

- STM32CubeIDE or STM32CubeMX
- STM32 HAL UART enabled
- C++ toolchain support in your STM32 project
- Nextion HMI display & Nextion Editor

---

## 📁 Folder Structure

```
├── Core
│   ├── Inc
│   │   └── nextion.h        # C++ class interface
│   └── Src
│       └── nextion.cpp      # Class implementation
├── README.md
```

---

## ⚙️ Basic Usage

1. **Include the header in your `.cpp` file:**
   ```cpp
   #include "nextion.h"
   ```

2. **Create a `Nextion` instance and initialize:**
   ```cpp
   extern UART_HandleTypeDef huart1;
   Nextion nex(&huart1);
   ```

3. **Send commands to the Nextion display:**
   ```cpp
   nex.sendCommand("page 0");
   nex.setText("t0", "Hello World!");
   ```

4. **Read response (if needed):**
   ```cpp
   std::string result = nex.receive();
   ```

---

## 🔧 Configuration Tips

- Use `.cpp` files for all your logic using this library.
- Wrap C headers like `main.h` or HAL includes in `extern "C"` if included in `.cpp` files.
- Ensure STM32CubeIDE is set to compile C++ files (rename `main.c` to `main.cpp` if needed).
- Disable unused C++ features (like RTTI/exceptions) in project settings for smaller binaries.

---

## 📚 References

- [Nextion Instruction Set](https://nextion.tech/instruction-set/)
- [Nextion Editor](https://nextion.tech/nextion-editor/)
- [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html)

---

## 🤝 Contributing

Contributions are welcome! Please feel free to fork this project, submit pull requests, or open issues to improve the library.

---

## 📄 License

This project is licensed under the **MIT License** – see the [LICENSE](LICENSE) file for details.

---

## 👤 Author

Developed by **[Aldrin Rebellow](https://github.com/aldrinrebellow7)**  
🔗 [LinkedIn](https://www.linkedin.com/in/aldrinrebellow)
