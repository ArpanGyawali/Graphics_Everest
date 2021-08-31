#pragma once
#include "mesh.h"
#include "Mat4.h"
#include "Vec3.h"
#include "newCamera.h"
#include <vector>
#include "Light.h"
#include "clipping.h"
#include "Vertex.h"
#include "ConvertToScreen.h"
#include "DrawInterpolatedTriangle.h"
#include <algorithm>
#include <list>
#include <iterator>
#include "texLoad.h"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum class Camera_Movement {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    AKEY,
    SKEY,
    DKEY,
    WKEY,
    ZKEY,
    XKEY,
    CKEY,
    VKEY,
    RKEY,
    TKEY,
    YKEY,
    FKEY,
    GKEY,
    HKEY,
    PKEY,
};


class Pipeline
{
private:
	mesh meshModel;
    float thetaX, thetaY, thetaZ;
    float yawY;
    Vec3f vLookDir;
    Vec3f vCamera;
    float lightX, lightY, lightZ;
    Image img;
    bool isWire;;
    //float* pDepthBuffer = nullptr;
public:
    Pipeline()
        :
        thetaX(0.0), thetaY(0.0), thetaZ(0.0), yawY(0.0), lightX(-10), lightY(-100), lightZ(-100), isWire(false),
        vLookDir(Vec3f(0.0, 0.0, -1.0)), vCamera(Vec3f(0.0, 0.0, 20.0))/*vCamera(Vec3f(200.0, 13000.0, -19000.0))*/     //SCALING:10-->(-1900.0, 146940.0, -177770.0))      //eiffel (0.0,0.0,0.0)
    {
        if (!meshModel.LoadFromObjectFile("OBJFiles/Everest7.obj"))
        {
            std::cerr << "Model not loaded";
        }
        else {
            std::cout << "Model Loaded";
        }

        std::string filename = "OBJFiles/Mount1.jpg";

        //int width, height;
        bool success = img.load(filename);
        if (success){
            std::cout << "image loaded\n";
        }
        else
        {
            std::cout << "Error loading image\n";
        }
        //pDepthBuffer = new float[WIDTH * HEIGHT];
    }

    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        Vec3f vForward = vLookDir * (10.0f * deltaTime);                             //eiffel(0.2 * deltatime)
        if (direction == Camera_Movement::UP)
            vCamera.y += 10.0 * deltaTime;                 //500
        if (direction == Camera_Movement::DOWN)
            vCamera.y -= 10.0 * deltaTime;
        if (direction == Camera_Movement::LEFT)
            vCamera.x -= 10.0 * deltaTime;
        if (direction == Camera_Movement::RIGHT)
            vCamera.x += 10.0 * deltaTime;

        if (direction == Camera_Movement::WKEY)
            vCamera = vCamera + vForward;
        if (direction == Camera_Movement::SKEY)
            vCamera = vCamera - vForward;
        if (direction == Camera_Movement::AKEY)
            yawY -= 0.2f * deltaTime;                   //0.2
        if (direction == Camera_Movement::DKEY)                         
            yawY += 0.2f * deltaTime;
        if (direction == Camera_Movement::ZKEY)
            thetaX -= 0.4f * deltaTime;
        if (direction == Camera_Movement::XKEY)
            thetaX += 0.4f * deltaTime;
        if (direction == Camera_Movement::CKEY)
            thetaY -= 0.4f * deltaTime;
        if (direction == Camera_Movement::VKEY)
            thetaY += 0.4f * deltaTime;
        if (direction == Camera_Movement::RKEY)
            lightX += 5.0f;
        if (direction == Camera_Movement::TKEY)
            lightY += 5.0f;
        if (direction == Camera_Movement::YKEY)
            lightZ += 5.0f;
        if (direction == Camera_Movement::FKEY)
            lightX -= 5.0f;
        if (direction == Camera_Movement::GKEY)
            lightY -= 5.0f;
        if (direction == Camera_Movement::HKEY)
            lightZ -= 5.0f;
        if (direction == Camera_Movement::PKEY)
            isWire = isWire ? false : true;

        //std::cout << vCamera.x << " " << vCamera.y << " " << vCamera.z << std::endl;
        //std::cout << lightX << " " << lightY << " " << lightZ << std::endl;
    }
   
    void update()
    {
        //glLoadIdentity();
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       
        Drawtriangle trian(img);
        Vec3f Ka = Vec3f(1.0f, 1.0f, 1.0f);
        Vec3f Kd = Vec3f(0.8f, 0.8f, 0.8f);
        Vec3f Ks = Vec3f(0.5f, 0.5f, 0.5f);
        Vec3f light = Vec3f(lightX, lightY, lightZ);                //EIFIEL--->Vec3f(0.0, 500.0, 3.0);
        float ns = 225.0f;
        Vec3f Ia = Vec3f(1.0f, 1.0f, 1.0f);
        Vec3f Il = Vec3f(0.8f, 0.8f, 0.8f);
        Mat4f rotation =
            Mat4f::RotationX(thetaX) *
            Mat4f::RotationY(thetaY) *
            Mat4f::RotationZ(thetaZ);
        //Mat4f scaling = Mat4f::Scaling(2.0);
        Mat4f translate = Mat4f::Translation(0.0f, 0.0f, 100.0f);
        Mat4f matWorld = translate * rotation;                    //eifiel: no scaling

        Vec3f vUp = Vec3f(0.0, 1.0, 0.0);
        Vec3f vTarget = Vec3f(0.0, 0.0, 1.0);
        Mat4f matCameraRot = Mat4f::RotationY(yawY);
        vLookDir = matCameraRot * vTarget;
        vTarget = vCamera + vLookDir;

        // Make view matrix from camera
        Mat4f matView = calculateLookAt(vCamera, vTarget, vUp);

        // Store triagles for rastering later
        std::vector<triangle> vecTrianglesToRaster;

        //Draw Triangles
        for (auto& tri : meshModel.tris)
        {
            triangle triProjected, triTransformed, triViewed;

            // World Matrix Transform
            triTransformed.p[0] = matWorld * tri.p[0];
            triTransformed.p[1] = matWorld * tri.p[1];
            triTransformed.p[2] = matWorld * tri.p[2];
            //
            triTransformed.t[0] = tri.t[0];
            triTransformed.t[1] = tri.t[1];
            triTransformed.t[2] = tri.t[2];
            //
            triTransformed.n[0] = rotation * tri.n[0];
            triTransformed.n[1] = rotation * tri.n[1];
            triTransformed.n[2] = rotation * tri.n[2];

            // Calculate triangle Normal
            Vec3f normal, line1, line2;
            line1 = triTransformed.p[1] - triTransformed.p[0];
            line2 = triTransformed.p[2] - triTransformed.p[0];
            normal = line1.cross(line2);
            normal = normal.Normalize(normal);

            // Get Ray from triangle to camera
            Vec3f vCameraRay = triTransformed.p[0] - vCamera;
            vCameraRay = vCameraRay.Normalize(vCameraRay);

            // If ray is aligned with normal, then triangle is visible
            if (vCameraRay.dot(normal) < 0.0f)
            {
                Vec3f light_dir = light.Normalize(light);
                Vec3f p0 = triTransformed.p[0].Normalize(triTransformed.p[0]);
                Vec3f p1 = triTransformed.p[1].Normalize(triTransformed.p[1]);
                Vec3f p2 = triTransformed.p[2].Normalize(triTransformed.p[2]);
                triTransformed.c[0] = calculateIntensity(Ka, Kd, Ks, ns, p0, light_dir, vCameraRay, triTransformed.n[0], Ia, Il);
                triTransformed.c[1] = calculateIntensity(Ka, Kd, Ks, ns, p1, light_dir, vCameraRay, triTransformed.n[1], Ia, Il);
                triTransformed.c[2] = calculateIntensity(Ka, Kd, Ks, ns, p2, light_dir, vCameraRay, triTransformed.n[2], Ia, Il);

                //Convert World Space --> View Space
                triViewed.p[0] = matView * triTransformed.p[0];
                triViewed.p[1] = matView * triTransformed.p[1];
                triViewed.p[2] = matView * triTransformed.p[2];
                triViewed.n[0] = triTransformed.n[0];
                triViewed.n[1] = triTransformed.n[1];
                triViewed.n[2] = triTransformed.n[2];
                //
                triViewed.t[0] = triTransformed.t[0];
                triViewed.t[1] = triTransformed.t[1];
                triViewed.t[2] = triTransformed.t[2];
                //
                triViewed.c[0] = triTransformed.c[0];
                triViewed.c[1] = triTransformed.c[1];
                triViewed.c[2] = triTransformed.c[2];

                // Clip Viewed Triangle against near plane, this could form two additional triangles. 
                int nClippedTriangles = 0;
                triangle clipped[2];
                nClippedTriangles = Triangle_ClipAgainstPlane({ 0.0f, 0.0f, 0.9f }, { 0.0f, 0.0f, 1.0f }, triViewed, clipped[0], clipped[1]);

                // We may end up with multiple triangles form the clip, so project as required
                Mat4f matProj = Mat4f::PerspectiveFOV(90.0f, (float)HEIGHT / (float)WIDTH, 0.9f, -1.0f);
                for (int n = 0; n < nClippedTriangles; n++)
                {
                    //Convert View Space -->Clip space --> Projection Space
                    triProjected.p[0] = matProj * clipped[n].p[0];
                    triProjected.p[1] = matProj * clipped[n].p[1];
                    triProjected.p[2] = matProj * clipped[n].p[2];
                    triProjected.c[0] = clipped[n].c[0];
                    triProjected.c[1] = clipped[n].c[1];
                    triProjected.c[2] = clipped[n].c[2];
                    triProjected.t[0] = clipped[n].t[0];
                    triProjected.t[1] = clipped[n].t[1];
                    triProjected.t[2] = clipped[n].t[2];
                    triProjected.n[0] = clipped[n].n[0];
                    triProjected.n[1] = clipped[n].n[1];
                    triProjected.n[2] = clipped[n].n[2];

                    //
                    /*triProjected.t[0].x = triProjected.t[0].x / triProjected.p[0].w;
                    triProjected.t[1].x = triProjected.t[1].x / triProjected.p[1].w;
                    triProjected.t[2].x = triProjected.t[2].x / triProjected.p[2].w;

                    triProjected.t[0].y = triProjected.t[0].y / triProjected.p[0].w;
                    triProjected.t[1].y = triProjected.t[1].y / triProjected.p[1].w;
                    triProjected.t[2].y = triProjected.t[2].y / triProjected.p[2].w;

                    triProjected.t[0].w = 1.0f / triProjected.p[0].w;
                    triProjected.t[1].w = 1.0f / triProjected.p[1].w;
                    triProjected.t[2].w = 1.0f / triProjected.p[2].w;*/
                    //

                    // Scale into view, we moved the normalising into cartesian space
                    triProjected.p[0] = triProjected.p[0] / triProjected.p[0].w;
                    triProjected.p[1] = triProjected.p[1] / triProjected.p[1].w;
                    triProjected.p[2] = triProjected.p[2] / triProjected.p[2].w;

                    // X/Y are inverted so put them back
                    triProjected.p[0].x *= -1.0f;
                    triProjected.p[1].x *= -1.0f;
                    triProjected.p[2].x *= -1.0f;
                    triProjected.p[0].y *= -1.0f;
                    triProjected.p[1].y *= -1.0f;
                    triProjected.p[2].y *= -1.0f;

                    //Convert Projection Space --> Device Space
                    triProjected.p[0] = Transform(triProjected.p[0]);
                    triProjected.p[1] = Transform(triProjected.p[1]);
                    triProjected.p[2] = Transform(triProjected.p[2]);

                    vecTrianglesToRaster.push_back(triProjected);
                }
            }
        }
        sort(vecTrianglesToRaster.begin(), vecTrianglesToRaster.end(), [](triangle& t1, triangle& t2)
            {
                float z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0f;
                float z2 = (t2.p[0].z + t2.p[1].z + t2.p[2].z) / 3.0f;
                return z1 < z2;
            });

        ////Screen and Z buffer should be cleared
        //glClearColor(0.75, 1.0, 1.0, 0.7);
        ////  Clear screen and Z-buffer
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ///*for (int i = 0; i < WIDTH * HEIGHT; i++) {
        //    pDepthBuffer[i] = 0.0f;
        //}*/
        //glLoadIdentity();
        glColor3d(1.0, 1.0, 1.0);
        glBegin(GL_POLYGON);

        double locationX = lightX/1000.0;
        double locationY = lightY/800.0;
        double r = 0.03;

        for (double i = 0; i <= 360; i += 0.1)
        {
            glVertex2d(locationX + r * i, locationY + r * i);
        }

        glEnd();
        

        for (auto& triToRaster : vecTrianglesToRaster)
        {
            // Clip triangles against all four screen edges, this could yield
            // a bunch of triangles, so create a queue that we traverse to 
            //  ensure we only test new triangles generated against planes
            triangle clipped[2];
            std::list<triangle> listTriangles;

            // Add initial triangle
            listTriangles.push_back(triToRaster);
            int nNewTriangles = 1;

            for (int p = 0; p < 4; p++)
            {
                int nTrisToAdd = 0;
                while (nNewTriangles > 0)
                {
                    // Take triangle from front of queue
                    triangle test = listTriangles.front();
                    listTriangles.pop_front();
                    nNewTriangles--;

                    // Clip it against a plane. We only need to test each 
                    // subsequent plane, against subsequent new triangles
                    // as all triangles after a plane clip are guaranteed
                    // to lie on the inside of the plane. I like how this
                    // comment is almost completely and utterly justified
                    switch (p)
                    {
                    case 0:	nTrisToAdd = Triangle_ClipAgainstPlane({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, test, clipped[0], clipped[1]); break;
                    case 1:	nTrisToAdd = Triangle_ClipAgainstPlane({ 0.0f, (float)HEIGHT - 1, 0.0f }, { 0.0f, -1.0f, 0.0f }, test, clipped[0], clipped[1]); break;
                    case 2:	nTrisToAdd = Triangle_ClipAgainstPlane({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, test, clipped[0], clipped[1]); break;
                    case 3:	nTrisToAdd = Triangle_ClipAgainstPlane({ (float)WIDTH - 1, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, test, clipped[0], clipped[1]); break;
                    }

                    // Clipping may yield a variable number of triangles, so
                    // add these new ones to the back of the queue for subsequent
                    // clipping against next planes
                    for (int w = 0; w < nTrisToAdd; w++)
                        listTriangles.push_back(clipped[w]);
                }
                nNewTriangles = listTriangles.size();
            }
            // Draw the transformed, viewed, clipped, projected, sorted, clipped triangles
            for (auto& t : listTriangles)
            {
                Vertex v0(t.p[0], t.t[0], t.n[0], t.c[0]);
                Vertex v1(t.p[1], t.t[1], t.n[1], t.c[1]);
                Vertex v2(t.p[2], t.t[2], t.n[2], t.c[2]);
                trian.ProcessTriangle(v0, v1, v2);
                if (isWire)
                    trian.wireFrame(v0, v1, v2);
                /*TexturedTriangle(t.p[0].x, t.p[0].y, t.t[0].x, t.t[0].y, t.t[0].w,
                    t.p[1].x, t.p[1].y, t.t[1].x, t.t[1].y, t.t[1].w,
                    t.p[2].x, t.p[2].y, t.t[2].x, t.t[2].y, t.t[2].w, image);*/
                
                //DrawTriangle(t.p[0].x, t.p[0].y, t.p[1].x, t.p[1].y, t.p[2].x, t.p[2].y, PIXEL_SOLID, FG_BLACK);
            }
        }
    };

};