# Advanced Evasion Techniques Against Microsoft EDR and Cloud-Based Protection

This repository contains a detailed cybersecurity research report that evaluates and compares four advanced evasion techniques designed to bypass Microsoft Defender for Endpoint (EDR) and its cloud-based AI/ML protection layers.

📄 **Report:** [Advanced_Evasion_Report.pdf](Advanced_Evasion_Report.pdf)  
📅 **Submission Date:** July 22, 2025  
🎓 **Author:** Yazan Azmi Balawneh  
🏫 **University:** An-Najah National University — Faculty of Engineering and IT

---

## 📌 Objectives

- Evaluate modern evasion techniques (shellcode injection, direct syscalls, XLL, and covert C2).
- Test their effectiveness against Microsoft EDR and Defender Cloud Protection.
- Analyze stealth vs complexity vs detection.

---

## 🔬 Techniques Covered

1. **Early Cryo Bird Injection**  
   Uses Job Object freezing and APC to stealthily inject shellcode.

2. **Direct Syscalls with Encrypted Shellcode**  
   Executes XOR-encrypted shellcode via low-level NT syscalls using SysWhispers2.

3. **ZigStrike Injection (XLL + DLL)**  
   Utilizes the ZigStrike framework for stealthy shellcode loading via Excel XLL and SFX-wrapped DLL.

4. **Native Messaging API via Covert C2**  
   Establishes a local communication channel between a browser extension and a native app for command execution.

---

## 🛡️ Test Environment

- **OS:** Windows 10 Pro (Build 19045.5371)
- **Security:** Microsoft Defender EDR + Cloud AI (fully enabled)
- **Payloads:** Reverse shell EXE → Shellcode via Donut → XOR + Base64 encoding

---

## 📊 Summary Table

| Technique              | EDR Detection | Cloud Detection | Notes                             |
|------------------------|---------------|------------------|------------------------------------|
| Early Cryo Bird        | ❌ Not Detected | ✅ Detected     | Bypasses EDR but flagged by cloud |
| Direct Syscalls        | ❌ Not Detected | ✅ Detected     | Effective offline evasion         |
| ZigStrike (XLL)        | ❌ Not Detected | ❌ Not Detected | Blocked by Office trust policy    |
| ZigStrike (DLL + SFX)  | ✅ Detected     | ✅ Detected     | Signature-based detection         |
| Native Messaging C2    | ❌ Not Detected | ❌ Not Detected | Requires pre-installation         |

---

## 🧠 Key Takeaways

- Direct syscall injection remains highly effective against EDR.
- Cloud AI detection adds a robust second layer.
- Trusted application misuse (Office, browser extensions) offers stealth opportunities.
- Obsolete techniques like DLL injection require obfuscation or layering to remain viable.

---

## 📚 References

- [Early Cryo Bird Injection](https://github.com/zero2504/Early-Cryo-Bird-Injections)
- [Covert C2 – Native Messaging API](https://github.com/efchatz/Covert-C2)
- [ZigStrike Loader](https://github.com/gavz/ZigStrike_shellcode)
- [SysWhispers2](https://github.com/jthuraisamy/SysWhispers2)
- [Reflective DLL Injection](https://github.com/stephenfewer/ReflectiveDLLInjection)

---

> **Note:** This research is for educational and red team evaluation purposes only. All tests were conducted in controlled environments.
