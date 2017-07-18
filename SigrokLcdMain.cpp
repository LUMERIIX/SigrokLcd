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

using ctype=gboolean;
using sigrok::Packet;

//(*IdInit(SigrokLcdFrame)
const long SigrokLcdFrame::idMenuQuit = wxNewId();
const long SigrokLcdFrame::idMenuAbout = wxNewId();
const long SigrokLcdFrame::idMenuConnect = wxNewId();
const long SigrokLcdFrame::idMenuDisconnect = wxNewId();

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
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem3;
    wxMenuItem* MenuItem4;

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
    //*)

    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    wxBoxSizer* bSizer0 = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* bSizer1 = new wxBoxSizer(wxHORIZONTAL);
    lcd_ = new wxLCDWindow(this, wxDefaultPosition, wxSize(300, 120));
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


    bSizer1->Add(lcd_, 1, wxEXPAND, 5);
    bSizer1->Add(bSizer2, 0, wxEXPAND, 5);
//
    bSizer0->Add(bSizer1, 1, wxEXPAND, 5);
//    //bSizer0->Add(listbox1, 1, wxEXPAND, 5);
//
    this->SetSizer(bSizer0);
    this->Layout();
    bSizer0->Fit(this);



}

void SigrokLcdFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void SigrokLcdFrame::OnDisconnect(wxCommandEvent& event)
{
    session_->stop();
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
    if(IsEmpty(SelectedDriver))
        return;


    std::string SelectedDriver_std = std::string(SelectedDriver.mb_str());
    std::shared_ptr<sigrok::Driver> driver = driversMap[SelectedDriver_std];
    std::map<const sigrok::ConfigKey*, Glib::VariantBase> scanOptions;
    wxString CONN = wxGetTextFromUser(wxT("Serial Port"),wxT("Select Serial Port")/*,last_Conn*/);
    std::string CONN_std = std::string(CONN.mb_str());
    scanOptions[sigrok::ConfigKey::CONN] = Glib::Variant<Glib::ustring>::create(CONN_std);
    //scanOptions[sigrok::ConfigKey::SERIALCOMM] = Glib::Variant<Glib::ustring>::create(SERIALCOMM_std);
//      scanOptions[sigrok::ConfigKey::LIMIT_SAMPLES] = Glib::Variant<Glib::ustring>::create("1");
    std::vector<std::shared_ptr<sigrok::HardwareDevice>> hwDevs = driver->scan(scanOptions);
    if(hwDevs.size() <= 0)
        return;
    else
        ::wxMessageBox("Device found");
    std::shared_ptr<sigrok::HardwareDevice> hwDev = hwDevs[0];
    hwDev->open();

    session_ = context_->create_session();
    session_->add_device(hwDev);
    if(session_->devices().size() <= 0)
        return;

    wxString LIMITSAMPLES = wxGetTextFromUser(wxT("Amount of samples\n0 or empty enable continuous sampling"),wxT("Choose...")/*,last_Conn*/);
    uint64_t limitsamples = (uint64_t) wxAtoi(LIMITSAMPLES);
    wxString SAMPLERATE = wxGetTextFromUser(wxT("Samplerate \t[Hz]"),wxT("Choose..."));
    uint64_t samplerate = (uint64_t) wxAtoi(SAMPLERATE);
    hwDev->config_set(sigrok::ConfigKey::LIMIT_SAMPLES , Glib::Variant<uint64_t>::create(limitsamples));
    hwDev->config_set(sigrok::ConfigKey::SAMPLERATE , Glib::Variant<uint64_t>::create(samplerate));

//    if (hwDev->config_check(sigrok::ConfigKey::LIMIT_SAMPLES, sigrok::Capability::GET))
//    {
//       ::wxMessageBox("GET Posible");
////           auto gvar = hwDev->config_get(sigrok::ConfigKey::LIMIT_SAMPLES);
//       //::wxMessageBox("GET VAR");
////            sample_count = g_variant_get_uint64(gvar.gobj());
////            ::wxMessageBox("Transformed");
//
//    }

//    Glib::VariantContainerBase gvar_dict;
//    if (hwDev->config_check(sigrok::ConfigKey::TIMEBASE, sigrok::Capability::LIST))
//    {
//        ::wxMessageBox("LIST POSSIBLE");
//        gvar_dict = hwDev->config_list(sigrok::ConfigKey::TIMEBASE);
//        ::wxMessageBox("LIST SAVED");
//    }


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
    //::wxMessageBox("GET CONTEXt");

    //::wxMessageBox("started");

}
void SigrokLcdFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = _("LcdTest");
    wxMessageBox(msg, _("Welcome to..."));
}

void SigrokLcdFrame::sigrok_datafeed_callback(std::shared_ptr<sigrok::Device> hwDev, std::shared_ptr<sigrok::Packet> packet)
{
    //::wxMessageBox("sigrok_datafeed_callback");
    if(packet->type() == sigrok::PacketType::ANALOG)
    {
        std::shared_ptr<sigrok::Analog> analogPacket = std::dynamic_pointer_cast<sigrok::Analog>(packet->payload());

        float f;
        int i = 0;
        float exp_val = 0;
        float exp =1;
        float disp_val = 0;

            analogPacket->get_data_as_float(&f);

                ledmHz_->SetState(awxLED_OFF);
                ledHz_->SetState(awxLED_OFF);
                ledkHz_->SetState(awxLED_OFF);
                ledMHz_->SetState(awxLED_OFF);


                    exp_val = (log10(f));

                    wxString expval = wxString::Format(_T("%10.6f"), exp_val);
                    wxString getfloat = wxString::Format(_T("%10.6f"), f);
                    //::wxMessageBox("exp: %s",getfloat);


                    if(exp_val >= 6.0000)
                    {
                            exp_val = 6;
                            ledMHz_->SetState(awxLED_ON);
                    }
                    else if(exp_val >= 3.00000)
                    {
                            exp_val = 3;
                            ledkHz_->SetState(awxLED_ON);
                    }
                    else if(exp_val >= 0.00000)
                    {
                            exp_val = 0;
                            ledHz_->SetState(awxLED_ON);
                    }
                    else if(exp_val >= -3.00000)
                    {
                            exp_val = -3;
                            ledmHz_->SetState(awxLED_ON);
                    }

                    if(f<=0)
                    {
                        exp_val = 0;
                        ledHz_->SetState(awxLED_ON);
                    }


                    disp_val = f / pow(10,exp_val);

                wxString nextVal = wxString::Format(_T("%10.4f"), disp_val);
                lcd_->SetValue(nextVal);
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
    //::wxMessageBox("sigrok_stopped_callback");
}
