using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSFormSerp
{
    public partial class Form1 : Form
    {
        IDrawableArea drawableArea;

        #region temp
        int left = 100;
        int max_left = 200;
        int min_left = 0;
        int direction = 1;
        #endregion

        public Form1()
        {
            InitializeComponent();

            drawableArea = new Form1DrawableArea(this);
            this.timer1.Enabled = true;

            postInit();
        }

        protected void postInit()
        {
            //this->KeyDown += gcnew System.Windows.Forms.KeyEventHandler(this, &PlayForm.PlayFormKeyDown);
            //this->KeyUp += gcnew System.Windows.Forms.KeyEventHandler(this, &PlayForm.PlayFormKeyUp);
            SetStyle(ControlStyles.ResizeRedraw, true);
            SetStyle(ControlStyles.ResizeRedraw | ControlStyles.Opaque, true);
            

            SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.DoubleBuffer | ControlStyles.ResizeRedraw | ControlStyles.UserPaint, true);
            this.Focus();
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            //in meniu
            Graphics graphics = e.Graphics;
           
            this.drawableArea.newFrame();

            this.drawableArea.drawText("press <ENTER> to start gaming test", Color.Beige, 220, 240);
            this.drawableArea.drawText("ok?", Color.Beige, 220, 270);
            this.drawableArea.drawEllipse(Color.Azure, left, 240, 50, 10);
            this.drawableArea.drawOnGraphics(graphics);
            

            //graphics.DrawImage(localBitmap, 0, 0);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            // How much time has passed: timer1->Interval;
            if (direction == 1)
            {
                // move right
                if (left > max_left)
                {
                    left = max_left;
                    direction = -1;
                }
                else
                {
                    left += direction;
                }
            }
            else
            {
                if (left < min_left)
                {
                    left = min_left;
                    direction = 1;
                }
                else
                {
                    left += direction;
                }
            }

            // render the scene: invalidate the form to force redraw.
            this.Invalidate();

        }
    }
}
