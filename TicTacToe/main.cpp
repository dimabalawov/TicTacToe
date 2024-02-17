#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include "resource.h"
#pragma comment(lib, "comctl32.lib")



INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;
HWND hButton,hCheck;
bool isStep=1;
bool isGameWon = 0;
static short step = 0;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    hInst = hInstance;
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

void isGameOver(HWND hWnd)
{
    bool isWon = 0;
    WCHAR buttonText[9]{};
    int j = 0;
    for (size_t i = IDC_BUTTON1; i <= IDC_BUTTON9; i++)
    {
        WCHAR temp[2];
        GetWindowText(GetDlgItem(hWnd, i), temp, 2);
        buttonText[j] = temp[0];
        j++;
    }
    WCHAR symb = L'X';
    for (size_t i = 0; i < 2; i++)
    {
        if (i)
            symb = L'O';
        if (buttonText[0]==symb && buttonText[1] == symb&& buttonText[2] == symb)
            isWon = 1;
        if (buttonText[0] == symb && buttonText[4] == symb && buttonText[8] == symb)
            isWon = 1;
        if (buttonText[0] == symb && buttonText[1] == symb && buttonText[2] == symb)
            isWon = 1;
        if (buttonText[2] == symb && buttonText[5] == symb && buttonText[8] == symb)
            isWon = 1;
        if (buttonText[6] == symb && buttonText[7] == symb && buttonText[8] == symb)
            isWon = 1;
        if (buttonText[3] == symb && buttonText[4] == symb && buttonText[5] == symb)
            isWon = 1;
        if (buttonText[1] == symb && buttonText[4] == symb && buttonText[7] == symb)
            isWon = 1;
        if (buttonText[2] == symb && buttonText[4] == symb && buttonText[6] == symb)
            isWon = 1;
        if (isWon)
        {
            isGameWon = 1;
            for (size_t i = IDC_BUTTON1; i <= IDC_BUTTON9; i++)
            {
                HWND button = GetDlgItem(hWnd, i);
                EnableWindow(button, FALSE);
            }
            if (i)
                MessageBox(hWnd, L"Игра окончена. Нолики Выиграли", 0, 0);
            else
                MessageBox(hWnd, L"Игра окончена. Крестики Выиграли", 0, 0);
            return;
        }
    }
}

INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{

    switch (message)
    {
    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;
    case WM_INITDIALOG:
        for (size_t i = IDC_BUTTON1; i <= IDC_BUTTON9; i++)
        {
            HWND button = GetDlgItem(hWnd, i);
            EnableWindow(button, FALSE);
        }
        hCheck = GetDlgItem(hWnd, IDC_CHECK1);
        return TRUE;
    case WM_COMMAND:
        if (HIWORD(wp) == BN_CLICKED) {
            int controlId = LOWORD(wp);
            if (controlId >= IDC_BUTTON1 && controlId <= IDC_BUTTON9)
            {
                HWND button = GetDlgItem(hWnd, controlId);
                WCHAR buttonText[2];
                GetWindowText(button, buttonText, 2);
                if (buttonText[0] == L'X' || buttonText[0] == L'O')
                {
                    MessageBox(hWnd, L"Клетка занята", 0, 0);
                }
                else
                {
                    isStep == 1 ? SetWindowText(button, L"X") : SetWindowText(button, L"O");
                    isStep == 1 ? isStep = 0 : isStep = 1;
                    step++;
                    if(step>4)
                        isGameOver(hWnd);
                    if (step == 9 && !isGameWon)
                    {
                        for (size_t i = IDC_BUTTON1; i <= IDC_BUTTON9; i++)
                        {
                            HWND button = GetDlgItem(hWnd, i);
                            EnableWindow(button, FALSE);
                        }
                        MessageBox(hWnd, L"Игра окончена. Все ячейки заняты", 0, 0);
                        step = 0;
                    }
                }
            }
        }
        if (HIWORD(wp) == BN_CLICKED && LOWORD(wp) == IDC_BUTTON10)
        {
            for (size_t i = IDC_BUTTON1; i <= IDC_BUTTON9; i++)
            {
                HWND button = GetDlgItem(hWnd, i);
                EnableWindow(button, TRUE);
                SetWindowText(button, L"");
            }
            bool state = SendMessage(hCheck, BM_GETCHECK, 0, 0);
            state == 0 ? isStep = 1 : isStep = 0;
        }
        return TRUE;
    }
    return FALSE;
}