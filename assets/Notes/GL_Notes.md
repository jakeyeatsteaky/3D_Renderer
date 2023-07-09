www.learnopengl.com

Transformations:
{
    Unit vector:
        - a vector that has been "normalized" by dividing it by its magnitude:
            vector a = (1,2,3); |a| = sqrt(1 + 4 + 9)
            vector u is a normalized / unit vector
            therefore: u = a / |a| 
                  __        __
                 | 1/sqrt(14) | 
             u = | 2/sqrt(14) |
                 | 3/sqrt(14) |
                  --        --
    
    Dot Product:
        a_vec = (x,y,z); b_vec = (d,e,f);
        a_vec . b_vec = x*x + y*e + z*f --> returns a scalar
        a_vec . b_vec = |a||b|cos(@) where @ is the angle between a and b

    Cross Product:
        - Takes two non parallel 3D vectors and produces a third vector orthogonal to both input vectors.
        
        vector_1 = a b c    vector_2 = d e f

        vector_1 x vector_2 = vector_3
                    +  -  +
                    a  b  c
                    d  e  f

               vector_3 = [(bf-ce), -(af-cd), (ae-db)]

    Matrix Operations:
        - Non-commutative: A.B != B.A
        - Matrix-Vector Multiplication:
            - The nature of transformation involves performing a matrix operation on a vector.  Basically performing some math (matrix) on some point (vector)

            a b c d          
            e f g h     4x4 homoegeneous matrix
            i j k l
            m n o p

            abc                                  a 0 0
            efg the 3x3 transformation matrix -> 0 f 0
            ijk                                  0 0 k

            mnop -> 0 0 0 1 for homogeneity

            d
            h --> the translation vector
            l 

    Rotation:
        - Angle in degress = angle in radians * (180/pi)
        - angle in radians = angle in degress * (pi/180)

}


Coordinate Systems
{
    - After each vertex shader run, OpenGL expects all vertices to be in Normalized Device Coordinates. [-1.0, 1.0]

    - Usually this is done by specifying a coordinate space ourselves (world space), transform into NDC in the vertex shader, then on rasterization, they are transformed to screen space (2d)
                                   camera
    - Local Space - World Space - View Space - Clip Space - Screen Space
          
    Local Space -> [Model Matrix] -> World Space
    World Space -> [View Matrix] -> View Space
    View Space -> [Projection Matrix] -> Clip Space

    Vclip =  Mproj * Mview * Mmodel * Vlocal

}