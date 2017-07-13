using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSFormSerp
{
    public class Form1DrawableArea : IDrawableArea
    {
        private Graphics bitmapGraphics;
        private int width;
        private int height;
        Bitmap backBuffer = null;
        public Form1DrawableArea(Form owner)
        {
            this.width = owner.ClientRectangle.Width;
            this.height = owner.ClientRectangle.Height;
        }


        public void drawEllipse(Color color, float centerX, float centerY, float width, float height)
        {
            Pen pen = new Pen(color);
            bitmapGraphics.DrawEllipse(pen, centerX, centerY, width, height);
        }

        public void drawLine(Color color, float fromX, float fromY, float toX, float toY)
        {
            throw new NotImplementedException();
        }

        public void drawOnGraphics(Graphics target)
        {
            target.DrawImageUnscaled(backBuffer, 0, 0);
        }

        public void drawRectangle(Color color, float left, float top, float width, float height)
        {
            throw new NotImplementedException();
        }

        public void drawText(string text, Color color, float fromX, float fromY)
        {
            Brush myBrush = new System.Drawing.SolidBrush(color);
            System.Drawing.Font myfont = new System.Drawing.Font(System.Drawing.FontFamily.GenericSansSerif, 10);
            bitmapGraphics.DrawString(text, myfont, myBrush, fromX, fromY);
        }

        public void newFrame()
        {
            if (null == backBuffer)
            {
                backBuffer = new Bitmap(width, height);
            }

            bitmapGraphics = Graphics.FromImage(backBuffer);
            bitmapGraphics.Clear(Color.Navy);

            bitmapGraphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
        }
    }
}
