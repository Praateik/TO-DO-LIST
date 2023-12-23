#pragma once
#include <wx/wx.h>
class MainFrame : public wxFrame
{
    public :
        MainFrame(const wxString& title);
    private :
        void CreateControls();
        void BindEventHandlers();

        void OnAddButtonClicked(wxCommandEvent& evt);
        void OnInputEnter(wxCommandEvent& evt);
        void OnListKeydown(wxKeyEvent& evt);
        void AddSavedTasks();
        void AddTaskFromInput();
        void DeleteSelectedText();
        void MoveSelectedTask(int offset);
        void SwapTasks(int i, int j);
        void OnClearButtonClicked(wxCommandEvent& evt);
        void OnWindowClosed(wxCloseEvent& evt);


        wxPanel* Panel;
        wxStaticText* headlineText;
        wxTextCtrl* inputField;
        wxButton* addButton;
        wxCheckListBox* myCheckListBox;
        wxButton* clearButton;
};