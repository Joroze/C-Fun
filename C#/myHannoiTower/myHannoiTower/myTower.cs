using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Text;
using System.Security.Permissions;
using System.Threading;
using System.Windows.Forms;

namespace myHannoiTower
{
    internal class Disc
    {
        public float x { get; set; }
        public float y { get; set; }
        public float width { get; set; }
        public float height { get; set; }

        public static List<Color> clist = new List<Color>() { Color.Blue, Color.Red, Color.Orange, Color.Green, Color.Purple, Color.DarkGray };

        public Disc(float x, float y, float width = 15, float height = 15)
        {
            this.x = x;
            this.y = y;
            this.width = width;
            this.height = height;
       }

        public void SetPosition(float x, float y)
        {
            this.x = x;
            this.y = y;
        }

    }

    internal class Peg
    {
  
        public Peg(float x, float y, char name)
        {
            this.name = name;
            this.x = x;
            this.y = y;
        }

        public char name { get; set; }
        public float x { get; set; }
        public float y { get; set; }

        public Stack<int> stack = new Stack<int>();

    }

    internal class MyTower
    {
        private readonly PictureBox pb;

        private readonly int nDiscs;

        private readonly Peg[] pegs;
        private readonly Disc[] disc;

        private readonly int tickSpeed;


        private Peg towerA; //0
        private Peg towerB; //1
        private Peg towerC; //2

        // default with diskAmnt = 6, tickSpeed measured in miliseconds (1000 ms = 1 second)
        public MyTower(PictureBox pb, int nDiscs = 6, int tickSpeed = 1000)
        {
            this.pb = pb;
            this.nDiscs = nDiscs;
            this.tickSpeed = tickSpeed * 1000;

            Console.WriteLine(@"Number of Disks: {0}", this.nDiscs);
            Console.WriteLine(@"# of moves to be done: {0}", Math.Pow(2, nDiscs) - 1);
            Console.WriteLine(@"Tick Speed: {0}", this.tickSpeed);

            var g = this.pb.CreateGraphics();

            g.Clear(Color.Khaki);

            // Set the pegs' positions and display
            pegs = new Peg[3];
            for (var i = 0; i < 3; i++)
            {
                pegs[i] = new Peg(143*i, pb.Height - 30 - pb.Height/2, Convert.ToChar(65+i));
                g.FillRectangle(new SolidBrush(Color.Black), pegs[i].x, pegs[i].y, 15, 200);
            }

            towerA = pegs[0];
            towerB = pegs[1];
            towerC = pegs[2];

            // Create the discs and set location to the first peg
            disc = new Disc[this.nDiscs];
            for (int i = nDiscs - 1; i >= 0; i--)
            {
                if (i == nDiscs)
                    disc[i] = new Disc(pegs[0].x, pb.Height - 50, 70 - i*10);

                else
                {
                    disc[i] = new Disc(pegs[0].x, pegs[0].y + (25 * i), 70 + i*10);
                }

                g.FillRectangle(new SolidBrush(Disc.clist[i]), disc[i].x, disc[i].y, disc[i].width,
                    disc[i].height);
                g.DrawString((i + 1).ToString(),
                    new Font(new FontFamily("Times New Roman"), 12, FontStyle.Regular, GraphicsUnit.Pixel),
                    new SolidBrush(Color.White), new PointF(disc[i].x, disc[i].y));
            }


            // the board
            g.FillRectangle(new SolidBrush(Color.Black), 0, pb.Height - 30, pb.Width, 30);
        }


        public void Start()
        {
            MoveTower(nDiscs, towerA, towerC, towerB);
        }

        public void MoveTower(int disk, Peg source, Peg dest, Peg spare)
        {
            RepaintDisplay();

            if (disk > 0)
            {
                MoveTower(disk - 1, source, spare, dest);


               
                disc[disk - 1].x = dest.x;


                //Debug Info to Console
                RepaintDisplay();
                Console.WriteLine("Move disk {0} from tower {1} to tower {2}", disk, source.name, dest.name);
                Thread.Sleep(tickSpeed);


                MoveTower(disk - 1, spare, dest, source);
            }

        }


        public void RepaintDisplay()
        {
            var g = pb.CreateGraphics();
            g.TextRenderingHint = TextRenderingHint.AntiAlias;

            g.Clear(Color.Khaki);


            //draw pegs
            for (var i = 0; i < 3; i++)
            {
                g.FillRectangle(new SolidBrush(Color.Black), pegs[i].x, pegs[i].y, 15, 200);
            }

            // draw disks
            for (int i = nDiscs - 1; i >= 0; i--)
            {
                g.FillRectangle(new SolidBrush(Disc.clist[i]), disc[i].x, disc[i].y, disc[i].width,
                    disc[i].height);

                g.DrawString((i + 1).ToString(),
                    new Font(new FontFamily("Times New Roman"), 12, FontStyle.Regular, GraphicsUnit.Pixel),
                    new SolidBrush(Color.White), new PointF(disc[i].x, disc[i].y));
            }


            // the board
            g.FillRectangle(new SolidBrush(Color.Black), 0, pb.Height - 30, pb.Width, 30);
        }
    }
}
