using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using Timer = System.Windows.Forms.Timer;

namespace myHannoiTower
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private MyTower tower;
        private bool resetClickedOnce = true;

        private Thread myThread;

        private Timer timer1, timer2;

        private void startButton_Click(object sender, EventArgs e)
        {
            myThread = new Thread(NewThread) {IsBackground = true};
            myThread.Start();       

            if (speedBar.Value != 0)
            {
                progressBar1.Value++;
                progressBar2.Value++;

                timer1 = new Timer {Enabled = true};
                timer1.Start();
                timer1.Interval = speedBar.Value*1000;
                progressBar1.Maximum = (int) (Math.Pow(2, Convert.ToInt32(textBox1.Text)) - 1);
                timer1.Tick += new EventHandler(timer1_Tick);

                timer2 = new Timer {Enabled = true};
                timer2.Start();
                timer2.Interval = 1000;
                progressBar2.Maximum = speedBar.Value;
                timer2.Tick += new EventHandler(timer2_Tick);
            }

            else
            {
                progressBar1.Value = progressBar1.Maximum;
            }

            //tower.repaintDisplay();

        }

        void timer1_Tick(object sender, EventArgs e)
        {

            if (progressBar1.Value != (Math.Pow(2, Convert.ToInt32(textBox1.Text)) - 1))
                progressBar1.Value++;
            else
                timer1.Stop();

        }

        void timer2_Tick(object sender, EventArgs e)
        {
            if (progressBar2.Value == speedBar.Value)
                progressBar2.Value = 1;
            else if (timer1.Enabled == false)
                timer2.Stop();
            else
                progressBar2.Value++;

        }

        // function for newly created thread to use to start the algorithm
        private void NewThread()
        {
            tower.Start();
        }

        private void resetButton_Click(object sender, EventArgs e)
        {
            
            if (myThread != null && myThread.IsAlive)
            {
                myThread.Abort();
            }

            if (timer1 != null && timer1.Enabled)
            {
                timer1.Stop();
            }

            progressBar1.Value = 0;
            progressBar2.Value = 0;


            var diskInput = Convert.ToInt32(textBox1.Text);

            if (diskInput < 1 || diskInput > 6)
            {
                MessageBox.Show(@"Error: You must input a number up to 6.");
                return;
            }

            

        

            if (resetClickedOnce)
            {
                startButton.Enabled = true;
                resetButton.Text = @"Reload Game";
                resetClickedOnce = false;
            }

            tower = new MyTower(pictureBox1, Convert.ToInt32(textBox1.Text), speedBar.Value);

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            resetButton.Focus();  
                
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start("www.joroze.com");
        }

        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) &&
    (e.KeyChar != '.'))
            {
                e.Handled = true;
            }

            // only allow one decimal point
            if ((e.KeyChar == '.') && ((sender as TextBox).Text.IndexOf('.') > -1))
            {
                e.Handled = true;
            }
        }
    }
}
