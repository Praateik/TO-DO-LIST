#include "MainFrame.h"
#include <wx/wx.h>
#include <vector>
#include <string>
#include<iostream>
#include "task.h"
MainFrame::MainFrame(const wxString& title) :wxFrame(nullptr,wxID_ANY, title)
{
    CreateControls();
    BindEventHandlers();
    AddSavedTasks();

}
void MainFrame::CreateControls()
{
    wxFont headlineFont(wxFontInfo(wxSize(0,36)).Bold());
    wxFont mainFont(wxFontInfo(wxSize(0,24)));
    Panel = new wxPanel(this);
    Panel->SetFont(mainFont);
    headlineText = new wxStaticText(Panel, wxID_ANY,"To-Do list",wxPoint(0,22),wxSize(800,-1),wxALIGN_CENTER_HORIZONTAL);
    headlineText->SetFont(headlineFont);
inputField = new wxTextCtrl(panel,wxID_ANY,"",wxPoint(100,80), wxSize(495,35), wxTE_PROCESS_ENTER);
addButton = new wxButton(panel, wxID_ANY,"Add",wxPoint(600,80),wxSize(100,35));
myCheckListBox = new wxCheckListBox(panel,exID_ANY, wxPoint(100,120), wxSize(600,400));
clearButton = new wxButton(panel, wxID_ANY, "Clear", wxPoint(100,525), wxSize(100,35));
}

void MainFrame::BindEventHandlers()
{
    addButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddButtonClicked,this);
    inputField->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnInputEnter,this);
    myCheckListBox->Bind(wxEVT_KEY_DOWN, &MainFrame::OnListKeydown,this);
    clearButton->Bind(wxEVT_BUTTON, &MainFrame::OnClearButtonClicked,this);
    this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnWindowClosed,this);

}
void MainFrame::AddSavedTasks()
{
    std::vector<Task> tasks = loadTasksFromFile("tasks.txt");
    for (const Task& task : tasks)
    {
        int index = myCheckListBox->GetCount();
        myCheckListBox->Insert(task.description,index);
        myCheckListBox->Check(index,task.done);
    }
}
void MainFrame::OnAddButtonClicked(wxCommandEvent& evt)
{
    AddTaskFromInput();
}
void MainFrame::OnInputEnter(wxCommandEvent& evt)
{
    AddTaskFromInput();
}
void MainFrame::OnListKeydown(wxCommandEvent& evt)
{
    switch(evt.GetKeyCode())
    {
        case WXK_DELETE;
            DeleteSelectedText();
            break ;
        case WXK_UP;
            MoveSelectedTask(-1);
        case WXK_DOWN;
            MoveSelectedTask(1);
            break ;
    }
}
void MainFrame::OnWindowClosed(wxCloseEvent& evt)
{
    std::vector<Task> tasks;
    for(int i=0;i< myCheckListBox->GetCount();i++)
    {
        Task task;
        task.description = myCheckListBox->GetString(i);
        task.done = myCheckListBox->IsChecked(i);
        tasks.push_back(task);
    }
    SaveTasksToFile(tasks, "tasks.txt");
    evt.Skip();
}
void MainFrame::AddTaskFromInput()
{
    wxString description = inputField->GetValue();
    if(!description.IsEmpty())
        {
            myCheckListBox->Insert(description,myCheckListBox->GetCount());
            inputField->Clear();
        }
        inputField->SetFocus();

}

void MainFrame :: DeleteSelectedText()
{
    int SelectedIndex = myCheckListBox->GetSelection();
    if(SelectedIndex == wxNOT_FOUND)
    {
        return;
    }
    myCheckListBox->Delete(SelectedIndex);
}
void MainFrame::MoveSelectedTask(int offset)
{
    int SelectedIndex = myCheckListBox->GetSelection();
    if (SelectedIndex == wxNOT_FOUND)
    {
        return ;
    }
    int newIndex = SelectedIndex + offset;
    if (newIndex >= 0 && newIndex < myCheckListBox-> GetCount())
    {
        SwapTasks(SelectedIndex, newIndex);
        myCheckListBox->SetSelection(newIndex, true);
    }
}
void MainFrame::SwapTasks(int i , int j)
{
    Task taskI{myCheckListBox->GetString(i).ToStdString(), myCheckListBox->IsChecked(i)};
    Task taskJ{ myCheckListBox-> GetString(i).ToStdString(), myCheckListBox->IsChecked(j)};

    myCheckListBox->SetString(i,taskJ.description);
    myCheckListBox->Check(i, taskJ.done);

    myCheckListBox->SetString(j,taskI.description);
    myCheckListBox->Check(j, taskI.done);
}
void MainFrame::OnClearButtonClicked(wxCommandEvent& evt)
{
    if(myCheckListBox->IsEmpty())
    {
        return ;
    }
    wxMessageDialog dialog(this,"Are you sure you want to clear all tasks?","Clear", wxYES_NO | wxCANCEL);
    int result = dialog.ShowModal();
    if (result == wxID_YES)
    {
        myCheckListBox->Clear(); 
    }
}