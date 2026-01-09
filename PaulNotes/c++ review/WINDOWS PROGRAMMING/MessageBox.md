MessageBox(NULL, the actual message, the name of the message box, NULL)

to output what was pressed
```c++
AHmessage = (L" You pressed ");
AHmessage += std::btowc(wParam); // byteToWideCharacter
MessageBox(NULL, AHmessage.c_str(), L"YIPPEE", NULL);
```
