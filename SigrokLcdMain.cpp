/***************************************************************
 * Name:      SigrokLcdMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2017-05-31
 * Copyright:  ()
 * License:
 **************************************************************/

#include "SigrokLcdMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(SigrokLcdFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>

#include "lcdwindow.h"
#include "led.h"

#include <libsigrokcxx/libsigrokcxx.hpp>
#include <unistd.h>
#include <tgmath.h>
#include <wx/listbox.h>
#include <wx/textdlg.h>
#include <wx/config.h>
#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/wxprec.h>
#include <wx/bookctrl.h>
#include <wx/choicdlg.h>
#include <wx/event.h>
#include <string.h>
#include <stdio.h>

#include <libserialport.h>

struct sp_port *port;
struct sp_port **ports;

using ctype=gboolean;
using sigrok::Packet;

//(*IdInit(SigrokLcdFrame)
const long SigrokLcdFrame::idMenuQuit = wxNewId();
const long SigrokLcdFrame::idMenuAbout = wxNewId();
const long SigrokLcdFrame::idMenuConnect = wxNewId();
const long SigrokLcdFrame::idMenuDisconnect = wxNewId();
const long SigrokLcdFrame::idMenuCalibration = wxNewId();

const long SigrokLcdFrame::ID_STATUSBAR1 = wxNewId();

//*)

BEGIN_EVENT_TABLE(SigrokLcdFrame,wxFrame)
    //(*EventTable(SigrokLcdFrame)
    //*)
END_EVENT_TABLE()

//namespace
//{
//    SigrokLcdFrame *theSigrokLcdFrame;
//}



SigrokLcdFrame::SigrokLcdFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(SigrokLcdFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenu* Menu3;
    wxMenu* Menu4;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem3;
    wxMenuItem* MenuItem4;
    wxMenuItem* MenuItem5;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    Menu3 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu3, idMenuConnect, _("Select Driver\tF3"), _("Connect to Device"), wxITEM_NORMAL);
    MenuItem4 = new wxMenuItem(Menu3, idMenuDisconnect, _("Disconnect\tF4"), _("Disconnect from Device"), wxITEM_NORMAL);
    Menu3->Append(MenuItem3);
    Menu3->Append(MenuItem4);
    MenuBar1->Append(Menu3, _("Configure"));
    Menu4 = new wxMenu();
    MenuItem5 = new wxMenuItem(Menu4, idMenuCalibration, _("Calibrating Device\tF5"), _("Calibration of the Device"), wxITEM_NORMAL);
    Menu4->Append(MenuItem5);
    MenuBar1->Append(Menu4, _("Calibration"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SigrokLcdFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SigrokLcdFrame::OnAbout);
    Connect(idMenuConnect,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SigrokLcdFrame::OnConnect);
    Connect(idMenuDisconnect,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SigrokLcdFrame::OnDisconnect);
    Connect(idMenuCalibration,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SigrokLcdFrame::OnCalib);
    //*)
    //Bind(wxEVT_THREAD, &SigrokLcdFrame::OnThreadUpdate, this);

    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    wxBoxSizer* bSizer0 = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* bSizer1 = new wxBoxSizer(wxHORIZONTAL);
    lcd_ = new wxLCDWindow(this, wxDefaultPosition, wxSize(600, 240));
    lcd_->SetNumberDigits(10);
    lcd_->SetValue(_T("")); //lcd_->SetValue("");

    wxBoxSizer* bSizer2 = new wxBoxSizer(wxVERTICAL);
    bSizer2->AddStretchSpacer(1);

    ledmHz_ = new awxLed(this, wxID_ANY);
    ledmHz_->SetColour(awxLED_GREEN);
    wxStaticText *stxt = new wxStaticText(this, wxID_ANY, _T("mHz"));
    wxBoxSizer *bSizer3 = new wxBoxSizer(wxHORIZONTAL);
    bSizer3->Add(ledmHz_);
    bSizer3->Add(stxt);
    bSizer2->Add(bSizer3,0);

    ledHz_ = new awxLed(this, wxID_ANY);
    ledHz_->SetColour(awxLED_GREEN);
    //ledHz_->SetState(awxLED_ON);
    stxt = new wxStaticText(this, wxID_ANY, _T("Hz"));
    bSizer3 = new wxBoxSizer(wxHORIZONTAL);
    bSizer3->Add(ledHz_);
    bSizer3->Add(stxt);
    bSizer2->Add(bSizer3,0);

    ledkHz_ = new awxLed(this, wxID_ANY);
    ledkHz_->SetColour(awxLED_GREEN);
    ledkHz_->SetState(awxLED_OFF);
    stxt = new wxStaticText(this, wxID_ANY, _T("kHz"));
    bSizer3 = new wxBoxSizer(wxHORIZONTAL);
    bSizer3->Add(ledkHz_);
    bSizer3->Add(stxt);
    bSizer2->Add(bSizer3,0);

    ledMHz_ = new awxLed(this, wxID_ANY);
    ledMHz_->SetColour(awxLED_GREEN);
    stxt = new wxStaticText(this, wxID_ANY, _T("MHz"));
    bSizer3 = new wxBoxSizer(wxHORIZONTAL);
    bSizer3->Add(ledMHz_);
    bSizer3->Add(stxt);
    bSizer2->Add(bSizer3,0);
    ledState_ = 2;

    bSizer2->AddStretchSpacer(1);

    wxArrayString MeasChannels;
    wxArrayString RefChannels;
    wxArrayString Gatetime;
    MeasChannels.Add(wxT("CHA"));
    MeasChannels.Add(wxT("CHB"));
    RefChannels.Add(wxT("Int.Ref"));
    RefChannels.Add(wxT("Ext.Ref"));
    Gatetime.Add(wxT("10ms"));
    Gatetime.Add(wxT("100ms"));
    Gatetime.Add(wxT("1s"));
    Gatetime.Add(wxT("10s"));
    wxBoxSizer *CHSizer = new wxBoxSizer(wxHORIZONTAL);
    ChannelSelect = new wxComboBox(this,id,wxT("Measure Ch."),wxDefaultPosition,wxSize(1,40),MeasChannels,0,wxDefaultValidator,wxT("Channel"));
    CHSizer->Add(ChannelSelect,5,wxALL,1);
    RefChannelSelect = new wxComboBox(this,id,wxT("Reference Ch."),wxDefaultPosition,wxSize(1,40),RefChannels,0,wxDefaultValidator,wxT("Channel"));
    CHSizer->Add(RefChannelSelect,5,wxALL,1);
    GateTime = new wxComboBox(this,id,wxT("GateTime"),wxDefaultPosition,wxSize(1,40),Gatetime,0,wxDefaultValidator,wxT("Channel"));
    CHSizer->Add(GateTime,5,wxALL,1);

    ChannelSelect->Connect(wxEVT_COMBOBOX, wxKeyEventHandler(SigrokLcdFrame::RefreshParameters),NULL,this);
    RefChannelSelect->Connect(wxEVT_COMBOBOX, wxKeyEventHandler(SigrokLcdFrame::RefreshParameters),NULL,this);
    GateTime->Connect(wxEVT_COMBOBOX, wxKeyEventHandler(SigrokLcdFrame::RefreshParameters),NULL,this);

    bSizer1->Add(lcd_, 1, wxEXPAND, 5);
    bSizer1->Add(bSizer2, 0, wxEXPAND, 5);
//
    bSizer0->Add(bSizer1, 1, wxEXPAND, 5);
       bSizer0->Add(CHSizer, 0, wxEXPAND, 0);
//    //bSizer0->Add(listbox1, 1, wxEXPAND, 5);
//
    this->SetSizer(bSizer0);
    this->Layout();
    bSizer0->Fit(this);

}

void SigrokLcdFrame::RefreshParameters(wxKeyEvent& event)
{
    int GateTimeSel = 0;
    GateTimeSel = (GateTime->GetSelection())+2;
    Timebase = GateTime->GetString(GateTimeSel);
    int MeasChannelSel = 0;
    MeasChannelSel = ChannelSelect->GetSelection();
    MeasChannel = ChannelSelect->GetString(MeasChannelSel);
    int RefChannelSel = 0;
    RefChannelSel = RefChannelSelect->GetSelection();
    RefChannel = RefChannelSelect->GetString(RefChannelSel);
    session_->stop();

    session_ = context_->create_session();
    session_->add_device(hwDev);
    hwDev->config_set(sigrok::ConfigKey::DATA_SOURCE , Glib::Variant<Glib::ustring>::create(MeasChannel));
    hwDev->config_set(sigrok::ConfigKey::DEVICE_MODE , Glib::Variant<Glib::ustring>::create(RefChannel));
    hwDev->config_set(sigrok::ConfigKey::LIMIT_MSEC , Glib::Variant<uint64_t>::create(GateTimeSel));

    while(1)
    {
        hwDev->config_set(sigrok::ConfigKey::LIMIT_SAMPLES , Glib::Variant<uint64_t>::create(1));
        hwDev->config_set(sigrok::ConfigKey::SAMPLERATE , Glib::Variant<uint64_t>::create(samplerate));
        auto dfcb = [=](std::shared_ptr<sigrok::Device> device, std::shared_ptr<sigrok::Packet> packet)
        {
            this->sigrok_datafeed_callback(device, packet);
        };

        session_->add_datafeed_callback(dfcb);



        session_->set_stopped_callback(
            [=]() {
                sigrok_stopped_callback();
            }
        );

        session_->start();
        session_->run();
    }


    //Bind(wxEVT_COMMAND_MENU_SELECTED,&SigrokLcdFrame::OnConnect,this,wxID_ANY);
}

void SigrokLcdFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void SigrokLcdFrame::OnDisconnect(wxCommandEvent& event)
{
    session_->stop();
}

void SigrokLcdFrame::OnCalib(wxCommandEvent& event)
{
    //session_->stop();
}

void SigrokLcdFrame::OnConnect(wxCommandEvent& event)
{

    context_ = sigrok::Context::create();
    std::map<std::string, std::shared_ptr<sigrok::Driver>>  driversMap = context_->drivers();
    //static auto logCallback = [txtCtrl] (sigrok::LogLevel level, std::string str) {txtCtrl->AppendText(wxString::FromUTF8(str.c_str()));txtCtrl->AppendText(_T("\n"));};;
//    context_->set_log_callback(logCallback);
//    void set_log_level( LogLevel = context_->log_level());

    std::string lib_version = context_->lib_version();
    wxArrayString Multimeters;
    for (auto driverEntry : driversMap)
    {
        std::shared_ptr<sigrok::Driver> driver = driverEntry.second;
        std::set<const sigrok::ConfigKey *> configKeys = driver->config_keys();//scan_options();

        for (auto key : configKeys)
        {
            if ( key == sigrok::ConfigKey::MULTIMETER )
            {
                wxString str (wxString::FromUTF8(driverEntry.first.c_str()));
                Multimeters.Add(str);
            }
        }
    }

    wxString SelectedDriver = wxGetSingleChoice(wxT("Select One of the Drivers"),wxT("Select..."),Multimeters,lcd_);
    wxString last_Conn;
    if(wxIsEmpty(SelectedDriver))
        return;


    std::string SelectedDriver_std = std::string(SelectedDriver.mb_str());
    std::shared_ptr<sigrok::Driver> driver = driversMap[SelectedDriver_std];
    std::map<const sigrok::ConfigKey*, Glib::VariantBase> scanOptions;

    wxArrayString SerialPorts;
    sp_list_ports(&ports);
    char serialports[50] = {0};
    int i = 0;
    for(i = 0;ports[i];i++)
    {
        sprintf(serialports,"%s",sp_get_port_name(ports[i]));
        wxString strports (wxString::FromUTF8(serialports));
        SerialPorts.Add(strports);
    }

    wxString CONN = wxGetSingleChoice(wxT("Select One of the COM Ports"),wxT("Select..."),SerialPorts,lcd_);
    //wxString CONN = wxGetTextFromUser(wxT("Serial Port"),wxT("Select Serial Port")/*,last_Conn*/);

    std::string CONN_std = std::string(CONN.mb_str());
    scanOptions[sigrok::ConfigKey::CONN] = Glib::Variant<Glib::ustring>::create(CONN_std);
    //scanOptions[sigrok::ConfigKey::SERIALCOMM] = Glib::Variant<Glib::ustring>::create(SERIALCOMM_std);
//      scanOptions[sigrok::ConfigKey::LIMIT_SAMPLES] = Glib::Variant<Glib::ustring>::create("1");
    std::vector<std::shared_ptr<sigrok::HardwareDevice>> hwDevs = driver->scan(scanOptions);
    if(hwDevs.size() <= 0)
    {
        ::wxMessageBox("No Device found");
                return;
    }
    hwDev = hwDevs[0];
    hwDev->open();


    //if(session_->devices().size() <= 0)

//    wxString LIMITSAMPLES = wxGetTextFromUser(wxT("Amount of samples\n0 or empty enable continuous sampling"),wxT("Choose...")/*,last_Conn*/);
//    uint64_t limitsamples = (uint64_t) wxAtoi(LIMITSAMPLES);
    wxString SAMPLERATE = wxGetTextFromUser(wxT("Samplerate \t[Hz]"),wxT("Choose..."));
    samplerate = (uint64_t) wxAtoi(SAMPLERATE);

    session_ = context_->create_session();
    session_->add_device(hwDev);



    while(1)
    {
        hwDev->config_set(sigrok::ConfigKey::LIMIT_SAMPLES , Glib::Variant<uint64_t>::create(1));
        hwDev->config_set(sigrok::ConfigKey::SAMPLERATE , Glib::Variant<uint64_t>::create(samplerate));
        hwDev->config_set(sigrok::ConfigKey::DATA_SOURCE , Glib::Variant<Glib::ustring>::create(MeasChannel));
        hwDev->config_set(sigrok::ConfigKey::DEVICE_MODE , Glib::Variant<Glib::ustring>::create(RefChannel));
//        hwDev->config_set(sigrok::ConfigKey::CHANNEL_CONFIG , Glib::Variant<Glib::ustring>::create(MeasChannel));
//        hwDev->config_set(sigrok::ConfigKey::DEVICE_MODE , Glib::Variant<Glib::ustring>::create(RefChannel));
//        hwDev->config_set(sigrok::ConfigKey::TIMEBASE , Glib::Variant<Glib::ustring>::create(Timebase));


        auto dfcb = [=](std::shared_ptr<sigrok::Device> device, std::shared_ptr<sigrok::Packet> packet)
        {
            this->sigrok_datafeed_callback(device, packet);
        };

        session_->add_datafeed_callback(dfcb);



        session_->set_stopped_callback(
            [=]() {
                sigrok_stopped_callback();
            }
        );

        session_->start();
        session_->run();
    }

}
void SigrokLcdFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = _("LcdTest");
    wxMessageBox(msg, _("Welcome to..."));
}

void SigrokLcdFrame::sigrok_datafeed_callback(std::shared_ptr<sigrok::Device> hwDev, std::shared_ptr<sigrok::Packet> packet)
{
        float f;
//        int i = 0;
        int exp_val = 0;
//        float exp =1;
        wxString nextVal_old;
        float disp_val = 0;
    //::wxMessageBox("sigrok_datafeed_callback");
    if(packet->type() == sigrok::PacketType::ANALOG)
    {
        std::shared_ptr<sigrok::Analog> analogPacket = std::dynamic_pointer_cast<sigrok::Analog>(packet->payload());



        analogPacket->get_data_as_float(&f);

        ledmHz_->SetState(awxLED_OFF);
        ledHz_->SetState(awxLED_OFF);
        ledkHz_->SetState(awxLED_OFF);
        ledMHz_->SetState(awxLED_OFF);
        ledMHz_->Refresh();
        ledMHz_->Update();
        ledkHz_->Refresh();
        ledkHz_->Update();
        ledHz_->Refresh();
        ledHz_->Update();
        ledmHz_->Refresh();
        ledmHz_->Update();


        exp_val = (int)(log10(f));

        wxString expval = wxString::Format(_T("%i"), exp_val);
        wxString getfloat = wxString::Format(_T("%10.6f"), f);
        //::wxMessageBox("exp: %s",getfloat);


//        if(exp_val >= 6)
//        {
//                exp_val = 6;
//                ledMHz_->SetState(awxLED_ON);
//                ledMHz_->Refresh();
//                ledMHz_->Update();
//        }
//        else if(exp_val >= 3)
//        {
//                exp_val = 3;
//                ledkHz_->SetState(awxLED_ON);
//                ledkHz_->Refresh();
//                ledkHz_->Update();
//
//        }
//        else if(exp_val >= 0)
//        {
//                exp_val = 0;
//                ledHz_->SetState(awxLED_ON);
//                ledHz_->Refresh();
//                ledHz_->Update();
//        }
//        else if(exp_val >= -3)
//        {
//                exp_val = -3;
//                ledmHz_->SetState(awxLED_ON);
//                ledmHz_->Refresh();
//                ledmHz_->Update();
//        }

//        if(f<=0)
//        {
//            exp_val = 0;
//            ledHz_->SetState(awxLED_ON);
//        }


        disp_val = f / pow(10,exp_val);


        wxString nextVal = wxString::Format(_T("%10.6f"), disp_val);
        if (nextVal.Contains("-") || nextVal.Contains("") || nextVal.IsEmpty())
        {
            nextVal = nextVal_old;
        }
        else
        {
            if(exp_val >= 6)
            {
                exp_val = 6;
                ledMHz_->SetState(awxLED_ON);
                ledMHz_->Refresh();
                ledMHz_->Update();
            }
            else if(exp_val >= 3)
            {
                exp_val = 3;
                ledkHz_->SetState(awxLED_ON);
                ledkHz_->Refresh();
                ledkHz_->Update();

            }
            else if(exp_val >= 0)
            {
                exp_val = 0;
                ledHz_->SetState(awxLED_ON);
                ledHz_->Refresh();
                ledHz_->Update();
            }
            else if(exp_val >= -3)
            {
                exp_val = -3;
                ledmHz_->SetState(awxLED_ON);
                ledmHz_->Refresh();
                ledmHz_->Update();
            }

            nextVal_old = nextVal;
        }

//        wxString nextVal = wxString::Format(_T("%10.4f"), disp_val);
        //::wxMessageBox(("%s"),expval);
        lcd_->SetValue(nextVal);
        lcd_->Refresh();
        lcd_->Update();
        }

}

SigrokLcdFrame::~SigrokLcdFrame()
{
    //(*Destroy(LcdTestFrame)
    //*)
}

void SigrokLcdFrame::sigrok_stopped_callback()
{
    session_->stop();
}
