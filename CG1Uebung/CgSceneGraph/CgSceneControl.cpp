#include "CgSceneControl.h"
#include "CgBase/CgEnums.h"
#include "CgEvents/CgMouseEvent.h"
#include "CgEvents/CgKeyEvent.h"
#include "CgEvents/CgWindowResizeEvent.h"
#include "CgEvents/CgLoadObjFileEvent.h"
#include "CgEvents/CgTrackballEvent.h"
#include "CgEvents/CgColorChangeEvent.h"
#include "../CgEvents/CgSchritteAusfuehrenEvent.h"
#include "../CgEvents/CgSchritteResetEvent.h"
#include "../CgEvents/CgRotationskoerperErstellenEvent.h"
#include "../CgEvents/CgRotationskoerperNormalenEvent.h"
#include "CgRotation.h"
#include "CgBase/CgBaseRenderer.h"
#include "CgExampleTriangle.h"
#include "CgPolyline.h"
#include "CgDice.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtx/string_cast.hpp"
#include "CgUtils/ObjLoader.h"
#include <string>
#include "glm/gtx/string_cast.hpp"

bool draw_dice = false;
bool draw_dice_normals = false;
bool draw_polyline = true;

CgSceneControl::CgSceneControl()
{
    m_dice=nullptr;
    m_polyline = nullptr;
    m_rotation = nullptr;
    m_current_transformation=glm::mat4(1.);
    m_lookAt_matrix= glm::lookAt(glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
    m_proj_matrix= glm::mat4x4(glm::vec4(1.792591, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.792591, 0.0, 0.0), glm::vec4(0.0, 0.0, -1.0002, -1.0), glm::vec4(0.0, 0.0, -0.020002, 0.0));
    m_trackball_rotation=glm::mat4(1.);



    if(draw_polyline)
    {
        m_polyline = new CgPolyline(32);
        m_rotation = new CgRotation(50, m_polyline->getVertices(), 4);

        //std::cout <<  m_polyline->getVertices().size() << std::endl;
    }

    if (draw_dice)
    {
        m_dice = new CgDice(31);
        if(draw_dice_normals)
        {
            m_dice->calculate_normals();
        }
    }
}


CgSceneControl::~CgSceneControl()
{
    if (m_polyline != NULL && draw_polyline)
    {
        delete m_polyline;
    }

    if(m_dice!=NULL)
    {
        delete m_dice;

        if (m_dice->getNormals().size() > 0)
        {
            for(long i = 0; i < m_dice->getNormals().size(); i++){
                delete m_dice->getNormals().at(i);
            }
        }

    }
}

void CgSceneControl::setRenderer(CgBaseRenderer* r)
{
    m_renderer=r;
    m_renderer->setSceneControl(this);

    if(m_polyline!=NULL)
    {
        m_renderer->init(m_polyline);
    }

    if(m_dice!=NULL)
    {
        m_renderer->init(m_dice);

        if (m_dice->getNormals().size() > 0)
        {
            for(long i = 0; i < m_dice->getNormals().size(); i++)
            {
                m_renderer->init(m_dice->getNormals().at(i));
            }
        }
    }

    m_renderer->setUniformValue("mycolor",glm::vec4(0.0,1.0,0.0,1.0));
}


void CgSceneControl::renderObjects()
{
    // Materialeigenschaften setzen
    // sollte ja eigentlich pro Objekt unterschiedlich sein können, naja bekommen sie schon hin....

    //m_renderer->setUniformValue("mycolor",glm::vec4(0.0,1.0,0.0,1.0));

    m_renderer->setUniformValue("matDiffuseColor",glm::vec4(0.35,0.31,0.09,1.0));
    m_renderer->setUniformValue("lightDiffuseColor",glm::vec4(1.0,1.0,1.0,1.0));

    m_renderer->setUniformValue("matAmbientColor",glm::vec4(0.25,0.22,0.06,1.0));
    m_renderer->setUniformValue("lightAmbientColor",glm::vec4(1.0,1.0,1.0,1.0));

    m_renderer->setUniformValue("matSpecularColor",glm::vec4(0.8,0.72,0.21,1.0));
    m_renderer->setUniformValue("lightSpecularColor",glm::vec4(1.0,1.0,1.0,1.0));

    glm::mat4 mv_matrix = m_lookAt_matrix * m_trackball_rotation* m_current_transformation ;
    glm::mat3 normal_matrix = glm::transpose(glm::inverse(glm::mat3(mv_matrix)));

    m_renderer->setUniformValue("projMatrix",m_proj_matrix);
    m_renderer->setUniformValue("modelviewMatrix",mv_matrix);
    m_renderer->setUniformValue("normalMatrix",normal_matrix);



    if(m_polyline!=NULL)
    {
        m_renderer->render(m_polyline);
    }

    if(m_dice!=NULL)
    {
        m_renderer->render(m_dice);

        if (m_dice->getNormals().size() > 0)
        {
            for(long i = 0; i < m_dice->getNormals().size(); i++)
            {
                m_renderer->render(m_dice->getNormals().at(i));
            }
        }
    }


}



void CgSceneControl::handleEvent(CgBaseEvent* e)
{
    // die Enums sind so gebaut, dass man alle Arten von MausEvents über CgEvent::CgMouseEvent abprüfen kann,
    // siehe dazu die CgEvent enums im CgEnums.h

    if(e->getType() & Cg::CgRotationskoerperNormalenEvent){
        CgRotationskoerperNormalenEvent* ev = (CgRotationskoerperNormalenEvent*)e;

        if (ev->getZeichnen())
        {
            std::cout << "Normalen gezeichnen" << std::endl;
        } else {
            std::cout << "Normalen gelöscht" << std::endl;
        }
    }

    if(e->getType() & Cg::CgRotationskoerperErstellenEvent){
        CgRotationskoerperErstellenEvent* ev = (CgRotationskoerperErstellenEvent*)e;

        std::cout << "Rotationskörper Erstellung gestartet, Anzahl Segmente: " << ev->getSegmente() << std::endl;

    }

    if(e->getType() & Cg::CgSchritteResetEvent){
        CgSchritteResetEvent* ev = (CgSchritteResetEvent*)e;

        auto id = m_polyline->getID();
        delete m_polyline;
        m_polyline = new CgPolyline(id);
        m_renderer->init(m_polyline);
        m_renderer->redraw();

        std::cout << "Reset ausgeführt" << std::endl;

    }

    if(e->getType() & Cg::CgSchritteAusfuehrenEvent){
        CgSchritteAusfuehrenEvent* ev = (CgSchritteAusfuehrenEvent*)e;

        m_polyline->startLaneRiesenfeldAlgo(ev->getSchritte());
        m_renderer->init(m_polyline);
        m_renderer->redraw();

        for(glm::vec3 s : m_polyline->getVertices())
        {
            std::cout << glm::to_string(s) << std::endl;
        }
        //std::cout << "Schritte ausgeführt: " << ev->getSchritte() << std::endl;
    }

    if(e->getType() & Cg::CgColorChangeEvent){
        CgColorChangeEvent* ev = (CgColorChangeEvent*)e;

        m_renderer->setUniformValue("mycolor",glm::vec4((double)ev->red()/255,(double)ev->green()/255,(double)ev->blue()/255, 1.0));

        std::cout << "R:" << ev->red() << " G:" << ev->green() << " B:" << ev->blue() << std::endl;

        m_renderer->redraw();
    }

    if(e->getType() & Cg::CgMouseEvent)
    {
        CgMouseEvent* ev = (CgMouseEvent*)e;
        std::cout << *ev << std::endl;

        // hier kommt jetzt die Abarbeitung des Events hin...
    }


    if(e->getType() & Cg::CgTrackballEvent)
    {
        CgTrackballEvent* ev = (CgTrackballEvent*)e;


        m_trackball_rotation=ev->getRotationMatrix();
        m_renderer->redraw();

    }


    // die Enums sind so gebaut, dass man alle Arten von KeyEvents über CgEvent::CgKeyEvent abprüfen kann,
    // siehe dazu die CgEvent enums im CgEnums.h
    // momentan werden nur KeyPressEvents gefangen.

    if(e->getType() & Cg::CgKeyEvent)
    {
        CgKeyEvent* ev = (CgKeyEvent*)e;
        std::cout << *ev <<std::endl;

        if(ev->text()=="+")
        {
            glm::mat4 scalemat = glm::mat4(1.);
            scalemat = glm::scale(scalemat,glm::vec3(1.2,1.2,1.2));
            m_current_transformation=m_current_transformation*scalemat;
            m_renderer->redraw();
        }
        if(ev->text()=="-")
        {
            glm::mat4 scalemat = glm::mat4(1.);
            scalemat = glm::scale(scalemat,glm::vec3(0.8,0.8,0.8));

            m_current_transformation=m_current_transformation*scalemat;

            m_renderer->redraw();
        }
        // hier kommt jetzt die Abarbeitung des Events hin...
    }

    if(e->getType() & Cg::WindowResizeEvent)
    {
        CgWindowResizeEvent* ev = (CgWindowResizeEvent*)e;
        std::cout << *ev <<std::endl;
        m_proj_matrix=glm::perspective(45.0f, (float)(ev->w()) / ev->h(), 0.01f, 100.0f);
    }

    if(e->getType() & Cg::LoadObjFileEvent)
    {

        CgLoadObjFileEvent* ev = (CgLoadObjFileEvent*)e;


        ObjLoader* loader= new ObjLoader();
        loader->load(ev->FileName());

        std::cout << ev->FileName() << std::endl;

        std::vector<glm::vec3> pos;
        loader->getPositionData(pos);

        std::vector<glm::vec3> norm;
        loader->getNormalData(norm);

        std::vector<unsigned int> indx;
        loader->getFaceIndexData(indx);



        m_dice->init(pos,norm,indx);
        m_renderer->init(m_dice);
        m_renderer->redraw();
    }

    // an der Stelle an der ein Event abgearbeitet ist wird es auch gelöscht.
    delete e;


}
