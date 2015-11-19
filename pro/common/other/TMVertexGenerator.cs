using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ShapeBuilderClasses
{
    static public class TMVertexGenerator
    {
        /* Высчитывает координаты x,y,z каждой вершины 
         * поверхности по её параметрам U,V,a
         * */
        static public void calculateShape(out double x, out double y, out double z, double U, double V, double a)
        {
            // Conical spiral modification of cliffordtorus
            /*x = a * Math.Cos(10 * V + U + V) / (Math.Sqrt(2) + Math.Cos(V - U));
            y = a * Math.Sin(10 * V + U + V) / (Math.Sqrt(2) + Math.Cos(V - U));
            z = a * Math.Sin(V - U) / (Math.Sqrt(2) + Math.Cos(V - U)) + 100 * V;/**/

            // Spiral modification of cliffordtorus
            /*x = a * Math.Cos(U + V) / (Math.Sqrt(2) + Math.Cos(V - U));
            y = a * Math.Sin(U + V) / (Math.Sqrt(2) + Math.Cos(V - U));
            z = a * Math.Sin(V - U) / (Math.Sqrt(2) + Math.Cos(V - U)) + 30 * V;/**/

            // Сliffordtorus
            x = a * Math.Cos(U + V) / (Math.Sqrt(2) + Math.Cos(V - U));
            y = a * Math.Sin(U + V) / (Math.Sqrt(2) + Math.Cos(V - U));
            z = a * Math.Sin(V - U) / (Math.Sqrt(2) + Math.Cos(V - U));/**/

            // Hyperbolic-Helicoid
            /*double t = Math.Cosh(U) * Math.Cosh(V);
            x = a/2 * Math.Sinh(V) * Math.Cos(t * U);
            y = a/2 * Math.Sinh(V) * Math.Sin(t * U);
            z = a/2 * Math.Cosh(V) * Math.Sinh(U);/**/
            
            /* Catenoid
             * -1080 <= U <= 1080
             * -360 <= V <= 360
             * */
            /*x = Math.Cosh(V) * Math.Cos(U);
            y = Math.Cosh(V) * Math.Sin(U);
            z = U;/**/

            /* Helicoid
             * -1080 <= U <= 1080
             * -360 <= V <= 360
             * */
            /*x = Math.Sinh(V) * Math.Sin(U);
            y = Math.Sinh(V) * Math.Cos(U);
            z = V;/**/

            /*x = a * Math.Cosh(U) * Math.Cos(V);
            y = a * Math.Cosh(U) * Math.Sin(V);
            z = a * U;/**/

            // Ellipsoid a,b,c = a
            /*x = a * Math.Sin(U) * Math.Cos(V);
            y = a * Math.Sin(U) * Math.Sin(V);
            z = a * Math.Cos(U);/**/

            // Two-sheeted hyperboloid a,b,c = a
            /*x = a * Math.Cosh(U);
            y = a * Math.Sinh(U) * Math.Sin(V);
            z = a * Math.Sinh(U) * Math.Cos(V);/**/

            // One-sheeted hyperboloid a,b,c = a
            /*x = a * Math.Cosh(U) * Math.Cos(V);
            y = a * Math.Cosh(U) * Math.Sin(V);
            z = a * Math.Sinh(U);/**/

            // Conical spiral R = a, r = a/2, p = 40, k = 10
            /*x = (a + 40 * V + (a / 2) * Math.Cos(U)) * Math.Sin(V);
            y = (a + 40 * V + (a / 2) * Math.Cos(U)) * Math.Cos(V);
            z = (a / 2) * Math.Sin(U) + 10 * V;/**/

            // Spiral R = a, r = a/2, k = 30
           /* x = (a + (a/2) * Math.Cos(U)) * Math.Sin(V);
            y = (a + (a/2) * Math.Cos(U)) * Math.Cos(V);
            z = (a/2) * Math.Sin(U) + 30*V;/**/

            // Tor R = a, r = a/2
            /*x = (a + a/2 * Math.Cos(U)) * Math.Sin(V);
            y = (a + a/2 * Math.Cos(U)) * Math.Cos(V);
            z = (a/2) * Math.Sin(U);/**/

            // #####
            /*x = a / 2 * (1 + Math.Cos(V)) * Math.Cos(U);
            y = a / 2 * (1 + Math.Cos(V)) * Math.Sin(U);
            z = -Math.Tanh(U - Math.PI) * a * Math.Sin(V);/**/

            //Cross cup
            /*x = a * Math.Sin(U) * Math.Sin(2 * V);
            y = a * Math.Sin(2 * U) * Math.Sin(V) * Math.Sin(V);
            z = a * Math.Cos(2 * U) * Math.Sin(V) * Math.Sin(V);/**/

            //Astroidal ellipsoid
            /*x = a * Math.Pow(Math.Cos(U), 3) * Math.Pow(Math.Cos(V), 3);
            y = a * Math.Pow(Math.Sin(U), 3) * Math.Pow(Math.Cos(V), 3);
            z = a * Math.Pow(Math.Sin(V), 3);/**/

            // Eight surface
            /*x = a * Math.Cos(U) * Math.Sin(2 * V);
            y = a * Math.Sin(U) * Math.Sin(2 * V);
            z = a * Math.Sin(V);/**/

            /*x = a * Math.Sin(2 * U) * Math.Pow(Math.Sin(V), 2);
            y = a * Math.Sin(U) * Math.Cos(2 * V);
            z = a * Math.Cos(U) * Math.Sin(2 * V);/**/

            /*x = (a + a * Math.Cos(V)) * Math.Sin(U);
            y = (a + a * Math.Cos(V)) * Math.Cos(U);
            z = a * Math.Sin(U);/**/
        }

        /* Генерирует вершину p по переданным параметрам поверхности U,V,a
         * */
        static public void generateVertex(out TMVertex p, double U, double V, double a)
        {
            double x, y, z;
            calculateShape(out x, out y, out z, U, V, a);
            p = new TMVertex(x, y, z, 1);
        }
    }
}
