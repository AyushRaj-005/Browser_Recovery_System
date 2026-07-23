<div align="center">

![Header](https://capsule-render.vercel.app/api?type=waving&color=0:667eea,100:764ba2&height=200&section=header&text=Browser%20Session%20Recovery%20System&fontSize=38&fontColor=ffffff&animation=fadeIn&fontAlignY=38&desc=A%20Stack-based%20Browser%20Tab%20Manager%20built%20in%20C%2B%2B&descAlignY=58&descSize=18)

[![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)](#)
[![Data Structure](https://img.shields.io/badge/Data%20Structure-Stack%20(LIFO)-FF6B6B?style=for-the-badge)](#)
[![Status](https://img.shields.io/badge/Status-Completed-brightgreen?style=for-the-badge)](#)
[![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)](#)

<img src="https://skillicons.dev/icons?i=cpp,git,github,vscode" alt="tech stack" />

</div>

---

## 📌 About The Project

**Browser Session Recovery System** is a console-based, menu-driven C++ application that simulates real browser tab management — open, close, and instantly restore tabs — exactly like Chrome's "Reopen Closed Tab" feature.

At its core, the project demonstrates a clean, real-world application of the **Stack (LIFO)** data structure, combined with **File Handling** for session persistence and **Object-Oriented Programming** for clean code structure.

> 💡 Built as an academic Data Structures project — simple enough for a beginner to explain, yet structured like a real-world application.

---

## ✨ Features

| Feature | Description |
|---|---|
| 🗂️ Open New Tab | Push a new tab onto the `openTabs` stack |
| ❌ Close Current Tab | Pop from `openTabs`, push into `closedTabs` |
| ♻️ Restore Last Closed Tab | Pop from `closedTabs`, push back into `openTabs` |
| 📋 Show Open / Closed Tabs | View all tabs in LIFO order |
| 💾 Save / Load Session | Persist tabs to `session.txt` using File Handling |
| 🔍 Search Tab | Linear search by website name |
| 🧹 Clear All Tabs | Close all tabs at once (with confirmation) |
| 📊 Browser Statistics | Track opens, closes, restores, searches & saves |

---

## 🧠 Why Stack?

Browser tabs behave exactly like a stack — the tab you closed **last** is the one you want back **first**. This project turns that everyday intuition into working C++ code using `push_back()` / `pop_back()` on a `vector`, giving full LIFO control without relying on `std::stack`.
