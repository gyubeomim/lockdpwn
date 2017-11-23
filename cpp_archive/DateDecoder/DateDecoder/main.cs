using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Globalization;

namespace ARTeam_DateConverter
{
    public partial class main : Form
    {
        public main()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
            CenterToScreen();
        }

        private void Exit_Click(object sender, EventArgs e)
        {
            // The user wants to exit the application. Close everything down.
            Application.Exit();
        }

        private void main_Load(object sender, EventArgs e)
        {
            cbBias.SelectedIndex = 13;
            cbFormat.SelectedIndex = 0;
        }

        private void cbFormat_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch( cbFormat.SelectedIndex )
            {
                case 0:
                    txtExample.Text = "FF03D2315FE1C701";
                    break;
                case 1:
                    txtExample.Text = "01C7E15F31D202FF";
                    break;
                case 2:
                    txtExample.Text = "1713586176,30212469";
                    break;
                case 3:
                    txtExample.Text = "CD4E55C3:01C7DD3E";
                    break;
                case 4:
                    txtExample.Text = "FBE8DF975D3FE340";
                    break;
                case 5:
                    txtExample.Text = "D9070B00010002000600090013000000";
                    break;
                case 6:
                    txtExample.Text = "A2C3B446";
                    break;
                case 7:
                    txtExample.Text = "46C3B400";
                    break;
                case 8:
                    txtExample.Text = "1170245478";
                    break;
                case 9:
                    txtExample.Text = "1176469232719";
                    break;
                case 10:
                    txtExample.Text = "12883423549317375";
                    break;
                case 11:
                    txtExample.Text = "1230055555.77712";
                    break;
                case 12:
                    txtExample.Text = "219216022";
                    break;
                case 13:
                    txtExample.Text = "3561A436";
                    break;
                case 14:
                    txtExample.Text = "A4363561";
                    break;
                case 15:
                    txtExample.Text = "CD4E55C3";
                    break;
                case 16:
                    txtExample.Text = "C3554ECD";
                    break;
                case 17:
                    txtExample.Text = "CD4E55C3";
                    break;
                case 18:
                    txtExample.Text = "C3554ECD";
                    break;
                case 19:
                    txtExample.Text = "1221842272303080";
                    break;
                case 20:
                    txtExample.Text = "199231625.4";
                    break;
            }
        }

        private void ckbWindowTop_CheckedChanged(object sender, EventArgs e)
        {
            if (ckbWindowTop.CheckState == CheckState.Checked)
            {
                main.ActiveForm.TopMost = true;
            }
            else
            {
                main.ActiveForm.TopMost = false;
            }
        }

        private void DecodeButton_Click(object sender, EventArgs e)
        {
            string hexdate = txtValueToDecode.Text;
            int iBias = cbBias.SelectedIndex;
            string szUTC = "";
            switch(iBias){
                case 0:
                    szUTC = " UTC -12:00";
                    break;
                case 1:
                    szUTC = " UTC -11:00";
                    break;
                case 2:
                    szUTC = " UTC -10:00";
                    break;
                case 3:
                    szUTC = " UTC -09:00";
                    break;
                case 4:
                    szUTC = " UTC -08:00";
                    break;
                case 5:
                    szUTC = " UTC -07:00";
                    break;
                case 6:
                    szUTC = " UTC -06:00";
                    break;
                case 7:
                    szUTC = " UTC -05:00";
                    break;
                case 8:
                    szUTC = " UTC -04:00";
                    break;
                case 9:
                    szUTC = " UTC -03:30";
                    break;
                case 10:
                    szUTC = " UTC -03:00";
                    break;
                case 11:
                    szUTC = " UTC -02:00";
                    break;
                case 12:
                    szUTC = " UTC -01:00";
                    break;
                case 13:
                    szUTC = " UTC 00:00";
                    break;
                case 14:
                    szUTC = " UTC +01:00";
                    break;
                case 15:
                    szUTC = " UTC +02:00";
                    break;
                case 16:
                    szUTC = " UTC +03:00";
                    break;
                case 17:
                    szUTC = " UTC +03:30";
                    break;
                case 18:
                    szUTC = " UTC +04:00";
                    break;
                case 19:
                    szUTC = " UTC +04:30";
                    break;
                case 20:
                    szUTC = " UTC +05:00";
                    break;
                case 21:
                    szUTC = " UTC +05:30";
                    break;
                case 22:
                    szUTC = " UTC +05:45";
                    break;
                case 23:
                    szUTC = " UTC +06:00";
                    break;
                case 24:
                    szUTC = " UTC +06:30";
                    break;
                case 25:
                    szUTC = " UTC +07:00";
                    break;
                case 26:
                    szUTC = " UTC +08:00";
                    break;
                case 27:
                    szUTC = " UTC +09:00";
                    break;
                case 28:
                    szUTC = " UTC +09:30";
                    break;
                case 29:
                    szUTC = " UTC +10:00";
                    break;
                case 30:
                    szUTC = " UTC +11:00";
                    break;
                case 31:
                    szUTC = " UTC +12:00";
                    break;
                case 32:
                    szUTC = " UTC +13:00";
                    break;
            }
            switch( cbFormat.SelectedIndex )
            {   
                case 0: // Windows: 64Bit Hex Value - Little Endian
                    txtDateTime.Text = LittletoBigEndian64BitHexFormat(hexdate, iBias) + szUTC.ToString();
                    break;
                case 1: // Windows: 64Bit Hex Value - Big Endian
                    txtDateTime.Text = BigEndian64BitHexFormat(hexdate, iBias) + szUTC.ToString();
                    break;
                case 2: // Windows: IE Cookie Date (Lo Value, Hi Value)
                    txtDateTime.Text = WindowsIECookieFormat(hexdate, iBias) + szUTC.ToString();
                    break;
                case 3: // Windows: 32bit FileTime [xxxxxxxx:xxxxxxxx]
                    txtDateTime.Text = Win32FileTime(hexdate, iBias) + szUTC.ToString();
                    break;
                case 4: // Windows: OLE Automation Format (64bit Double)
                    txtDateTime.Text = OLEAutomationDateFormat(hexdate, iBias) + szUTC.ToString();
                    break;
                case 5: //Windows: 128 bit System Structure
                    txtDateTime.Text = WinSystemTime(hexdate, iBias) + szUTC.ToString();
                    break;
                case 6: // Unix: 32 bit Hex Value - Little Endian
                    txtDateTime.Text = UnixLittleEndianTime(hexdate, iBias) + szUTC.ToString();
                    break;
                case 7: // Unix: 32 bit Hex Value - Big Endian
                    txtDateTime.Text = UnixBigEndianTime(hexdate, iBias) + szUTC.ToString();
                    break;
                case 8: // Unix: Numeric Value
                    txtDateTime.Text = UnixSecondTime(hexdate, iBias) + szUTC.ToString();
                    break;
                case 9: // Unix: Milisecond Value
                    txtDateTime.Text = UnixMilliSecondTime(hexdate, iBias) + szUTC.ToString();
                    break;
                case 10: // Google ChromeWebKit Value
                    txtDateTime.Text = ChromeWebKitDateTime(hexdate, iBias) + szUTC.ToString();
                    break;
                case 11: // Google Chrome Value
                    txtDateTime.Text = ChromeDateTime(hexdate, iBias) + szUTC.ToString();
                    break;
                case 12: // MAC: Absolute Time
                    txtDateTime.Text = MacAbsoluteTime(hexdate, iBias) + szUTC.ToString();
                    break;
                case 13: // MS-DOS: 32 bit Hex Value
                    txtDateTime.Text = MSDos32BitTimeDate(hexdate, iBias) + szUTC.ToString();
                    break;
                case 14: // MS-DOS: wFatDate wFatTime
                    txtDateTime.Text = MSDos32BitDateTime(hexdate, iBias) + szUTC.ToString();
                    break;
                case 15: // HFS: 32 bit Hex Value - Little Endian
                    txtDateTime.Text = MacHFSLE(hexdate, iBias) + szUTC.ToString();
                    break;
                case 16: // HFS: 32 bit Hex Value - Big Endian
                    txtDateTime.Text = MacHFSBE(hexdate, iBias) + szUTC.ToString();
                    break;
                case 17: // HFS+: 32 bit Hex Value - Little Endian
                    txtDateTime.Text = MacHFSPlusLE(hexdate, iBias) + szUTC.ToString();
                    break;
                case 18: // HFS+: 32 bit Hex Value - Big Endian
                    txtDateTime.Text = MacHFSPlusBE(hexdate, iBias) + szUTC.ToString();
                    break;
                case 19: // Mozilla Firefox PRTime
                    txtDateTime.Text = FirefoxDateTime(hexdate, iBias) + szUTC.ToString();
                    break;
                case 20: // Safari DateTime
                    txtDateTime.Text = SafariDateTime(hexdate, iBias) + szUTC.ToString();
                    break;
            }
        }

        private string LittletoBigEndian64BitHexFormat(string hexDate, int iHours)
        {
            string result;
            try
            {
                result = FileTime(IPAddress.NetworkToHostOrder(long.Parse(hexDate, NumberStyles.HexNumber)).ToString("X16"), iHours);
            }
            catch
            {
                result = "Error in value entered.";
            }
            return result;
        }

        private string BigEndian64BitHexFormat(string hexDate, int iHours)
        {
            string result;
            try
            {
                result = FileTime(long.Parse(hexDate, NumberStyles.HexNumber).ToString("X16"), iHours);
            }
            catch
            {
                result = "Error in value entered";
            }
            return result;
        }

        private string WindowsIECookieFormat(string hexDate, int iHours)
        {
            string result;
            try
            {
                string[] array = StringSplitter(hexDate, ',');
                string text = array[0];
                string text2 = array[1];
                long num = long.Parse(text);
                long num2 = long.Parse(text2);
                text = num.ToString("X8");
                text2 = num2.ToString("X8");
                result = BigEndian64BitHexFormat(text2 + text, iHours);
            }
            catch
            {
                result = "Error in value entered.";
            }
            return result;
        }

        private string Win32FileTime(string hexDate, int iHours)
        {
            string result;
            try
            {
                result = BigEndian64BitHexFormat(StringSplitter(hexDate, ':', 1), iHours);
            }
            catch
            {
                result = "Error in value entered.";
            }
            return result;
        }

        private string OLEAutomationDateFormat(string hexDate, int iHours)
        {
            string result;
            try
            {
                DateTime dateTime = new DateTime(1899, 12, 30);
                DateTime dateTime2 = default(DateTime);
                double value = double.Parse(hexDate);
                double iNum = dHoursToNum(iHours);
                result = dateTime.AddHours(iNum).AddDays(value).ToString("ddd, dd MMM yyyy HH':'mm':'ss");
            }
            catch
            {
                result = "Error in value entered.";
            }
            return result;
        }

        private string WinSystemTime(string hexDate, int iHours)
        {
            string result;
            try{
                string[] array = new string[]{Left(Right(hexDate, 4), 2),Right(Right(hexDate, 4), 2),
                    Left(Right(Left(hexDate, 28), 4), 2), Right(Right(Left(hexDate, 28), 4), 2),
                    Left(Right(Left(hexDate, 24), 4), 2), Right(Right(Left(hexDate, 24), 4), 2),
                    Left(Right(Left(hexDate, 20), 4), 2), Right(Right(Left(hexDate, 20), 4), 2),
                    Left(Right(Left(hexDate, 16), 4), 2), Right(Right(Left(hexDate, 16), 4), 2),
                    Left(Right(Left(hexDate, 12), 4), 2), Right(Right(Left(hexDate, 12), 4), 2),
                    Left(Right(Left(hexDate, 8), 4), 2), Right(Right(Left(hexDate, 8), 4), 2),
                    Left(Left(hexDate, 4), 2), Right(Left(hexDate, 4), 2)
                };
                double iNum = dHoursToNum(iHours);
                string s = array[15] + array[14];
                int year = int.Parse(s, NumberStyles.HexNumber);
                string s2 = array[13] + array[12];
                int month = int.Parse(s2, NumberStyles.HexNumber);
                string s3 = array[9] + array[8];
                int day = int.Parse(s3, NumberStyles.HexNumber);
                string s4 = array[7] + array[6];
                int hour = int.Parse(s4, NumberStyles.HexNumber);
                string s5 = array[5] + array[4];
                int minute = int.Parse(s5, NumberStyles.HexNumber);
                string s6 = array[3] + array[2];
                int second = int.Parse(s6, NumberStyles.HexNumber);
                string s7 = array[1] + array[0];
                int millisecond = int.Parse(s7, NumberStyles.HexNumber);
                DateTime dateTime = new DateTime(year, month, day, hour, minute, second, millisecond);
                result = dateTime.AddHours(iNum).ToString("ddd, dd MMM yyyy HH':'mm':'ss.ffff");
            }catch{
                result = "Error in value entered.";
            }
            return result;
        }

        private string UnixLittleEndianTime(string hexDate, int iHours)
        {
            string result;
            try{
                string[] array = new string[]{Right(hexDate, 2), Left(Right(hexDate, 4), 2),
                    Left(Right(hexDate, 6), 2),Left(hexDate, 2)
                };
                double iNum = dHoursToNum(iHours);
                string s = array[0] + array[1] + array[2] + array[3];
                long num = long.Parse(s, NumberStyles.HexNumber);
                DateTime dateTime = new DateTime(1970, 1, 1);
                result = dateTime.AddHours(iNum).AddSeconds((double)num).ToString("ddd, dd MMM yyyy HH':'mm':'ss");
            }catch{
                result = "Error in value entered.";
            }
            return result;
        }

        private string UnixBigEndianTime(string hexDate, int iHours)
        {
            string result;
            try
            {
                long num = long.Parse(hexDate, NumberStyles.HexNumber);
                double iNum = dHoursToNum(iHours);
                DateTime dateTime = new DateTime(1970, 1, 1);
                result = dateTime.AddHours(iNum).AddSeconds((double)num).ToString("ddd, dd MMM yyyy HH':'mm':'ss");
            }
            catch
            {
                result = "Error in value entered.";
            }
            return result;
        }

        private string UnixSecondTime(string hexDate, int iHours)
        {
            string result;
            try
            {
                long num = long.Parse(hexDate);
                double iNum = dHoursToNum(iHours);
                DateTime dateTime = new DateTime(1970, 1, 1);
                result = dateTime.AddHours(iNum).AddSeconds((double)num).ToString("ddd, dd MMM yyyy HH':'mm':'ss");
            }
            catch
            {
                result = "Error in value entered.";
            }
            return result;
        }

        private string UnixMilliSecondTime(string hexDate, int iHours)
        {
            string result;
            try
            {
                long num = long.Parse(hexDate);
                double iNum = dHoursToNum(iHours);
                DateTime dateTime = new DateTime(1970, 1, 1);
                result = dateTime.AddHours(iNum).AddMilliseconds((double)num).ToString("ddd, dd MMM yyyy HH':'mm':'ss");
            }
            catch
            {
                result = "Error in value entered.";
            }
            return result;
        }

        private string ChromeWebKitDateTime(string hexDate, int iHours)
        {
            string result;
            try
            {
                double num = double.Parse(hexDate);
                DateTime dateTime = new DateTime(1601, 1, 1);
                DateTime dateTime2 = default(DateTime);
                double iNum = dHoursToNum(iHours);
                result = dateTime.AddHours(iNum).AddMilliseconds(num / 1000.0).ToString("ddd, dd MMM yyyy HH':'mm':'ss");
            }
            catch
            {
                result = "Error in value entered.";
            }
            return result;
        }

        private string ChromeDateTime(string hexDate, int iHours)
        {
            string result;
            try
            {
                double value = double.Parse(hexDate);
                DateTime dateTime = new DateTime(1970, 1, 1);
                DateTime dateTime2 = default(DateTime);
                double iNum = dHoursToNum(iHours);
                result = dateTime.AddHours(iNum).AddSeconds(value).ToString("ddd, dd MMM yyyy HH':'mm':'ss");
            }
            catch
            {
                result = "Error in value entered.";
            }
            return result;
        }

        private string MacAbsoluteTime(string hexDate, int iHours)
        {
            string result;
            try
            {
                long num = long.Parse(hexDate);
                DateTime dateTime = new DateTime(2001, 1, 1);
                double iNum = dHoursToNum(iHours);
                result = dateTime.AddHours(iNum).AddSeconds((double)num).ToString("ddd, dd MMM yyyy HH':'mm':'ss 'UTC'");
            }
            catch
            {
                result = "Error in value entered.";
            }
            return result;
        }

        private string MSDos32BitTimeDate(string hexDate, int iHours)
        {
            string result;
            try
            {
                string s = EndianSwapper(hexDate);
                int num = int.Parse(s, NumberStyles.HexNumber);
                int num2 = (int)(((long)num & (long)(unchecked(-65536))) >> 16);
                int num3 = num & 65535;
                double iNum = dHoursToNum(iHours);
                DateTime date = new DateTime(((num3 & 16256) >> 9) + 1980, (num3 & 480) >> 5, num3 & 31, (num2 & 63488) >> 11, (num2 & 2016) >> 5, (num2 & 31) * 2);
                result = DateTimeFormatter(date.AddHours(iNum), "F", "Local");
            }
            catch
            {
                result = "Error in value entered.";
            }
            return result;
        }

        private string MSDos32BitDateTime(string hexDate, int iHours)
        {
            string result;
            try
            {
                string str = Right(hexDate, 4);
                string str2 = Left(hexDate, 4);
                string s = EndianSwapper(str + str2);
                int num = int.Parse(s, NumberStyles.HexNumber);
                int num2 = (int)(((long)num & (long)(unchecked(-65536))) >> 16);
                int num3 = num & 65535;
                double iNum = dHoursToNum(iHours);
                DateTime date = new DateTime(((num3 & 16256) >> 9) + 1980, (num3 & 480) >> 5, num3 & 31, (num2 & 63488) >> 11, (num2 & 2016) >> 5, (num2 & 31) * 2);
                result = DateTimeFormatter(date.AddHours(iNum), "F", "Local");
            }
            catch
            {
                result = "Error in value entered.";
            }
            return result;
        }

        private string MacHFSLE(string hexDate, int iHours)
        {
            string result;
            try{
                string[] array = new string[]{Right(hexDate, 2), Left(Right(hexDate, 4), 2), 
                    Left(Right(hexDate, 6), 2), Left(hexDate, 2)
                };
                string s = array[0] + array[1] + array[2] + array[3];
                uint num = uint.Parse(s, NumberStyles.HexNumber);
                DateTime dateTime = new DateTime(1904, 1, 1);
                double iNum = dHoursToNum(iHours);
                result = DateTimeFormatter(dateTime.AddHours(iNum).AddSeconds(num), "F", "Local");
            }catch{
                result = "Error in value entered.";
            }
            return result;
        }

        private string MacHFSBE(string hexDate, int iHours)
        {
            string result;
            try
            {
                uint num = uint.Parse(hexDate, NumberStyles.HexNumber);
                DateTime dateTime = new DateTime(1904, 1, 1);
                double iNum = dHoursToNum(iHours);
                result = DateTimeFormatter(dateTime.AddHours(iNum).AddSeconds(num), "F", "Local");
            }
            catch
            {
                result = "Error in value entered.";
            }
            return result;
        }

        private string MacHFSPlusLE(string hexDate, int iHours)
        {
            string result;
            try
            {
                uint num = uint.Parse(IPAddress.HostToNetworkOrder(int.Parse(hexDate, NumberStyles.HexNumber)).ToString("X8"), NumberStyles.HexNumber);
                DateTime dateTime = new DateTime(1904, 1, 1);
                double iNum = dHoursToNum(iHours);
                result = dateTime.AddHours(iNum).AddSeconds(num).ToString("ddd, dd MMM yyyy HH':'mm':'ss");
            }
            catch
            {
                result = "Error in value entered.";
            }
            return result;
        }

        private string MacHFSPlusBE(string hexDate, int iHours)
        {
            string result;
            try
            {
                uint num = uint.Parse(hexDate, NumberStyles.HexNumber);
                DateTime dateTime = new DateTime(1904, 1, 1);
                double iNum = dHoursToNum(iHours);
                result = dateTime.AddHours(iNum).AddSeconds(num).ToString("ddd, dd MMM yyyy HH':'mm':'ss");
            }
            catch
            {
                result = "Error in value entered.";
            }
            return result;
        }

        private string FirefoxDateTime(string hexDate, int iHours)
        {
            string result;
            try
            {
                double num = double.Parse(hexDate);
                DateTime dateTime = new DateTime(1970, 1, 1);
                DateTime dateTime2 = default(DateTime);
                double iNum = dHoursToNum(iHours);
                result = dateTime.AddHours(iNum).AddMilliseconds(num / 1000.0).ToString("ddd, dd MMM yyyy HH':'mm':'ss");
            }
            catch
            {
                result = "Error in value entered.";
            }
            return result;
        }

        private string SafariDateTime(string hexDate, int iHours)
        {
            string result;
            try
            {
                double value = double.Parse(hexDate);
                DateTime dateTime = new DateTime(2001, 1, 1);
                DateTime dateTime2 = default(DateTime);
                double iNum = dHoursToNum(iHours);
                result = dateTime.AddHours(iNum).AddSeconds(value).ToString("ddd, dd MMM yyyy HH':'mm':'ss 'UTC'");
            }
            catch
            {
                result = "Error in value entered.";
            }
            return result;
        }

        private double dHoursToNum(int iHours)
        {
            double iNum = 0;
            switch (iHours)
            {
                case 0:
                    iNum = -12;
                    break;
                case 1:
                    iNum = -11;
                    break;
                case 2:
                    iNum = -10;
                    break;
                case 3:
                    iNum = -9;
                    break;
                case 4:
                    iNum = -8;
                    break;
                case 5:
                    iNum = -7;
                    break;
                case 6:
                    iNum = -6;
                    break;
                case 7:
                    iNum = -5;
                    break;
                case 8:
                    iNum = -4;
                    break;
                case 9:
                    iNum = -3.5;
                    break;
                case 10:
                    iNum = -3;
                    break;
                case 11:
                    iNum = -2;
                    break;
                case 12:
                    iNum = -1;
                    break;
                case 13:
                    iNum = 0;
                    break;
                case 14:
                    iNum = 1;
                    break;
                case 15:
                    iNum = 2;
                    break;
                case 16:
                    iNum = 3;
                    break;
                case 17:
                    iNum = 3.5;
                    break;
                case 18:
                    iNum = 4;
                    break;
                case 19:
                    iNum = 4.5;
                    break;
                case 20:
                    iNum = 5;
                    break;
                case 21:
                    iNum = 5.5;
                    break;
                case 22:
                    iNum = 5.25;
                    break;
                case 23:
                    iNum = 6;
                    break;
                case 24:
                    iNum = 6.5;
                    break;
                case 25:
                    iNum = 7;
                    break;
                case 26:
                    iNum = 8;
                    break;
                case 27:
                    iNum = 9;
                    break;
                case 28:
                    iNum = 9.5;
                    break;
                case 29:
                    iNum = 10;
                    break;
                case 30:
                    iNum = 11;
                    break;
                case 31:
                    iNum = 12;
                    break;
                case 32:
                    iNum = 13;
                    break;
            }
            return iNum;
        }

        private string FileTime(string hexDate, int iHours)
        {
            long fileTime = long.Parse(hexDate, NumberStyles.HexNumber);
            double iNum = dHoursToNum(iHours);
            return DateTime.FromFileTime(fileTime).ToUniversalTime().AddHours(iNum).ToString("ddd, dd MMM yyyy HH':'mm':'ss");
        }

        private string[] StringSplitter(string valueToSplit, char splitter)
        {
            string[] array = new string[1];
            return valueToSplit.Split(new char[]{splitter});
        }

        private string StringSplitter(string valueToSplit, char splitter, int order)
        {
            string[] array = new string[1];
            array = valueToSplit.Split(new char[]{splitter});
            if (order == 0)
            {
                return array[0] + array[1];
            }
            return array[1] + array[0];
        }

        private string Right(string Original, int Count)
        {
            if( Original==null || Original==string.Empty || Original.Length<Count ){
                return Original;
            }
            return Original.Substring(Original.Length - Count);
        }

        private string Left(string Original, int Count)
        {
            if (Original == null || Original == string.Empty || Original.Length < Count)
            {
                return Original;
            }
            return Original.Substring(0, Count);
        }

        private string EndianSwapper(string hexDate)
        {
            int length = hexDate.Length;
            int arg_0F_0 = hexDate.Length / 2;
            string result = "";
            long.Parse(hexDate, NumberStyles.HexNumber);
            int num = length;
            if (num <= 16)
            {
                if (num != 8)
                {
                    if (num == 16)
                    {
                        string[] array = new string[length / 2];
                        array[0] = Left(Right(hexDate, 4), 2);
                        array[1] = Right(hexDate, 2);
                        array[2] = Left(hexDate, 2);
                        array[3] = Right(Left(hexDate, 4), 2);
                        array[4] = Right(Left(hexDate, 4), 2);
                        array[5] = Right(Left(hexDate, 4), 2);
                        array[6] = Right(Left(hexDate, 4), 2);
                        array[7] = Right(Left(hexDate, 4), 2);
                    }
                }
                else
                {
                    string[] array2 = new string[length / 2];
                    array2[0] = Left(Right(hexDate, 4), 2);
                    array2[1] = Right(hexDate, 2);
                    array2[2] = Left(hexDate, 2);
                    array2[3] = Right(Left(hexDate, 4), 2);
                    result = array2[3] + array2[2] + array2[1] + array2[0];
                }
            }
            else
            {
                if (num != 32 && num != 64)
                {
                }
            }
            return result;
        }

        private string DateTimeFormatter(DateTime date, string format, string text)
        {
            string result;
            try
            {
                result = date.ToString(format) + " " + text;
            }
            catch
            {
                result = "Error in value";
            }
            return result;
        }

        private void ClearButton_Click(object sender, EventArgs e)
        {
            txtDateTime.Text = "";
            txtValueToDecode.Text = "";
        }

    }
}
