using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using YAT.View.Controls;

namespace COMrefresh
{
    class Program
    {
        static void Main(string[] args)
        {
            var v = new SerialPortSelection();
            v.RefreshPortList();
        }
    }
}
