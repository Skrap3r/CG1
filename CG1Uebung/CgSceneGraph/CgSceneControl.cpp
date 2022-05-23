﻿#include "CgSceneControl.h"
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
#include "../CgEvents/CgLokKoordZeichnenEvent.h"
#include "../CgEvents/CgTransaltionAusfuerenEvent.h"
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
#include "CgScenegraph.h"
#include "CgSceneGraphEntity.h"
#include <stack>
#include <math.h>

CgSceneControl::CgSceneControl()
{
    m_triangle=nullptr;
    m_dice=nullptr;
    m_polyline = nullptr;
    m_rotation = nullptr;
    m_localX = nullptr;

    eX = nullptr;
    eY = nullptr;
    eZ = nullptr;

    root1 = nullptr;
    root2 = nullptr;
    e1 = nullptr;
    e2 = nullptr;
    e3 = nullptr;
    e4 = nullptr;

    root = nullptr;
    root_table = nullptr;
    root_chair = nullptr;
    root_board = nullptr;
    root_chest = nullptr;

    tableplate = nullptr;
    chessBoard = nullptr;
    leg_1 = nullptr;
    leg_2 = nullptr;
    leg_3 = nullptr;
    leg_4 = nullptr;

    m_current_transformation=glm::mat4(1.);
    m_lookAt_matrix= glm::lookAt(glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
    m_proj_matrix= glm::mat4x4(glm::vec4(1.792591, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.792591, 0.0, 0.0), glm::vec4(0.0, 0.0, -1.0002, -1.0), glm::vec4(0.0, 0.0, -0.020002, 0.0));
    m_trackball_rotation=glm::mat4(1.);

    m_triangle= new CgExampleTriangle();
    //m_polyline = new CgPolyline();
    //m_dice = new CgDice();
    //m_dice->calculate_normals();
    //m_rotation = new CgRotation();

    //Uebung04();
    Uebung05();


    /*
    ObjLoader* loader= new ObjLoader();
    loader->load("/mnt/hgfs/Git/CG1/CG1Uebung/CgData/King.obj");

    std::cout << "King.obj" << std::endl;

    std::vector<glm::vec3> pos;
    loader->getPositionData(pos);

    std::vector<glm::vec3> norm;
    loader->getNormalData(norm);

    std::vector<unsigned int> indx;
    loader->getFaceIndexData(indx);

    m_triangle->init(pos,norm,indx);
    */

}

void CgSceneControl::Uebung05()
{
    m_dice = new CgDice();

    //Stuhl
    seat = new CgSceneGraphEntity();
    seat->setName("chair_seat");
    //seat->addListObject(m_dice);

    root_chair = new CgSceneGraphEntity();
    root_chair->setName("root_chair");
    root_chair->setCurrent_transformation(seat->getCurrent_transformation());
    root_chair->addChild(seat);


    //Kiste auf dem Tisch
    chestFloor = new CgSceneGraphEntity();
    chestFloor->setName("chest_Floor");
    //chestFloor->addListObject(m_dice);

    root_chest = new CgSceneGraphEntity();
    root_chest->setName("root_chest");
    root_chest->setCurrent_transformation(chestFloor->getCurrent_transformation());
    root_chest->addChild(chestFloor);


    //Schachbrett
    chessBoard = new CgSceneGraphEntity();
    chessBoard->setName("chess_Board");
    chessBoard->addListObject(m_dice);

    root_board = new CgSceneGraphEntity();
    root_board->setName("root_board");
    root_board->setCurrent_transformation(chessBoard->getCurrent_transformation());
    root_board->addChild(chessBoard);


    //Tisch
    leg_4 = new CgSceneGraphEntity();
    leg_4->setName("leg_4");
    leg_4->addListObject(m_dice);

    leg_3 = new CgSceneGraphEntity();
    leg_3->setName("leg_3");
    leg_3->addListObject(m_dice);

    leg_2 = new CgSceneGraphEntity();
    leg_2->setName("leg_2");
    leg_2->addListObject(m_dice);

    leg_1 = new CgSceneGraphEntity();
    leg_1->setName("leg_1");
    leg_1->addListObject(m_dice);

    tableplate = new CgSceneGraphEntity();
    tableplate->setName("tableplate");
    tableplate->addListObject(m_dice);
    tableplate->getAppearance().setObject_color(glm::vec3(0,1,0));

    root_table = new CgSceneGraphEntity();
    root_table->setName("root_table");
    root_table->setCurrent_transformation(tableplate->getCurrent_transformation());
    root_table->addChild(tableplate);
    root_table->addChild(leg_1);
    root_table->addChild(leg_2);
    root_table->addChild(leg_3);
    root_table->addChild(leg_4);
    root_table->addChild(root_board);
    root_table->addChild(root_chest);


    //Root Element
    root = new CgSceneGraphEntity();
    root->setName("m_root");
    root->setCurrent_transformation(glm::mat4(1.));
    root->addChild(root_table);
    root->addChild(root_chair);


    translate_obj(tableplate, glm::vec3(0,1,0));
    scale_obj(tableplate, glm::vec3(2,0.1,2));

    translate_obj(leg_1, glm::vec3(0.9,0,0.9));
    scale_obj(leg_1, glm::vec3(0.1,2,0.1));

    translate_obj(leg_2, glm::vec3(0.9,0,-0.9));
    scale_obj(leg_2, glm::vec3(0.1,2,0.1));

    translate_obj(leg_3, glm::vec3(-0.9,0,-0.9));
    scale_obj(leg_3, glm::vec3(0.1,2,0.1));

    translate_obj(leg_4, glm::vec3(-0.9,0,0.9));
    scale_obj(leg_4, glm::vec3(0.1,2,0.1));

    translate_obj(chessBoard, glm::vec3(0,1.075,0));
    scale_obj(chessBoard, glm::vec3(1.2,0.05,1.2));



    graph = new CgScenegraph(root);

    graph->createListOfEntitys(graph->getRoot());
    old_color = glm::vec4(graph->getListOfEntitys().at(graph->getListOfEntitys().size()-1)->getAppearance().getObject_color(), 1);
    current_Entity = root;
    count = 0;
}

void CgSceneControl::Uebung04()
{
    m_polyline = new CgPolyline();
    m_dice = new CgDice();

    root1 = new CgSceneGraphEntity();
    root2 = new CgSceneGraphEntity();
    e1 = new CgSceneGraphEntity();
    e2 = new CgSceneGraphEntity();
    e3 = new CgSceneGraphEntity();
    e4 = new CgSceneGraphEntity();

    root1->addChild(e1);
    root1->addChild(e2);
    root1->addChild(root2);
    root1->setCurrent_transformation(e1->getCurrent_transformation());
    root1->setName("Rootgroup");

    root2->addChild(e3);
    root2->addChild(e4);
    root2->setCurrent_transformation(e3->getCurrent_transformation());
    root2->setName("Group Rotationskörper");


    e1->addListObject(m_polyline);
    e1->setName("Polyline Rotationskörper: e1");
    e2->addListObject(m_dice);
    e2->setName("Dice: e2");

    e3->setName("Rotationskörper: e3");
    e4->setName("Normalen Rotationskörper: e4");

    /*
    e1->addChild(e2);
    e2->setParent(e1);

    e1->addChild(e3);
    e3->setParent(e1);

    e3->addChild(e4);
    e4->setParent(e3);
*/

    e2->getAppearance().setObject_color(glm::vec3(0.0,1.0,0.0));
    //e2->setCurrent_transformation(m_lookAt_matrix * e1->getCurrent_transformation()*glm::mat4(glm::vec4(1,0,0,0),glm::vec4(0,1,0,0),glm::vec4(0,0,1,0),glm::vec4(0,0,0,1)));
    translate_obj(e2, glm::vec3(0,0,-2));
    scale_obj(e2, glm::vec3(1,2,1));

    graph = new CgScenegraph(root1);

    graph->createListOfEntitys(graph->getRoot());
    old_color = glm::vec4(graph->getListOfEntitys().at(graph->getListOfEntitys().size()-1)->getAppearance().getObject_color(), 1);
    //e1->getAppearance().setObject_color(glm::vec4(1,0,0,1));
    current_Entity = root1;
    count = 0;
}


CgSceneControl::~CgSceneControl()
{
    if(m_triangle!=NULL)
        delete m_triangle;

    if(m_rotation != NULL)
    {
        delete m_rotation;
    }

    if(!m_normalsRotation.empty())
    {
        for(auto s : m_normalsRotation)
        {
            delete s;
        }
    }

    if (m_polyline != NULL)
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

    if(m_triangle!=NULL)
        m_renderer->init(m_triangle);

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

    //m_renderer->setUniformValue("mycolor",glm::vec4(0.0,1.0,0.0,1.0));
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

    glm::mat4 mv_matrix = m_lookAt_matrix * m_trackball_rotation* m_current_transformation;
    glm::mat3 normal_matrix = glm::transpose(glm::inverse(glm::mat3(mv_matrix)));

    m_renderer->setUniformValue("projMatrix",m_proj_matrix);
    //m_renderer->setUniformValue("modelviewMatrix",mv_matrix);
    m_renderer->setUniformValue("normalMatrix",normal_matrix);
    setCurrentMatrix();
    graph->render(m_renderer);
    if(m_triangle!=NULL)
        m_renderer->render(m_triangle);

    /*
    if(!m_normalsRotation.empty())
    {
        for(auto s : m_normalsRotation)
        {
            m_renderer->render(s);
        }
    }

    if(m_rotation!=NULL)
    {
        m_renderer->render(m_rotation);
    }

    if(m_polyline!=NULL)
    {
        //m_renderer->render(m_polyline);
    }

    if(m_dice!=NULL)
    {
        //m_renderer->render(m_dice);

        if (m_dice->getNormals().size() > 0)
        {
            for(long i = 0; i < m_dice->getNormals().size(); i++)
            {
                m_renderer->render(m_dice->getNormals().at(i));
            }
        }
    }
    */

}

void CgSceneControl::setCurrent_transformation(const glm::mat4 &current_transformation)
{
    m_current_transformation = current_transformation;
}

void CgSceneControl::setCurrentMatrix()
{
    glm::mat4 mv_matrix = m_lookAt_matrix * m_trackball_rotation* m_current_transformation;
    std::stack <glm::mat4> temp;
    temp.push(mv_matrix);
    graph->setModleview_matrix_stack(temp);
}

void CgSceneControl::iterate_graph(CgSceneGraphEntity* arg_child, glm::vec3 arg_color)
{
    arg_child->getAppearance().setObject_color(arg_color);

    for(auto ent : arg_child->getChildren())
    {
        if(ent != NULL)
        {
            iterate_graph(ent, arg_color);
        }
    }
}

void CgSceneControl::scale_obj(CgSceneGraphEntity *arg_entity, glm::vec3 arg_scale)
{;
    arg_entity->setCurrent_transformation(glm::scale(arg_entity->getCurrent_transformation(), arg_scale));
    //m_renderer->redraw();
}

void CgSceneControl::translate_obj(CgSceneGraphEntity *arg_entity, glm::vec3 arg_translation)
{
    arg_entity->setCurrent_transformation(glm::translate(arg_entity->getCurrent_transformation(), arg_translation));
    //m_renderer->redraw();
}

void CgSceneControl::rotate_obj(CgSceneGraphEntity *arg_entity, glm::vec3 arg_rotation, float arg_angle)
{
    arg_entity->setCurrent_transformation(glm::rotate(arg_entity->getCurrent_transformation(), arg_angle, arg_rotation));
    //m_renderer->redraw();

}

void CgSceneControl::handleEvent(CgBaseEvent* e)
{
    // die Enums sind so gebaut, dass man alle Arten von MausEvents über CgEvent::CgMouseEvent abprüfen kann,
    // siehe dazu die CgEvent enums im CgEnums.h

    if(e->getType() & Cg::CgTransaltionAusfuerenEvent)
    {
        CgTransaltionAusfuerenEvent* ev = (CgTransaltionAusfuerenEvent*)e;

        translate_obj(current_Entity, ev->getTranslation());
        m_renderer->redraw();
    }

    if(e->getType() & Cg::CgLokKoordZeichnenEvent)
    {
        CgLokKoordZeichnenEvent* ev = (CgLokKoordZeichnenEvent*)e;

        if (ev->getZeichnen())
        {
            glm::vec3 center;
            if(current_Entity->getList_of_objects().empty())
            {
                current_Entity->getChildren().at(0)->calculateCenter();
                center = current_Entity->getChildren().at(0)->getCenter();
            }
            else
            {
                current_Entity->calculateCenter();
                center = current_Entity->getCenter();
            }

            std::vector<glm::vec3> temp;

            temp.push_back(center);


            temp.push_back(center + glm::vec3(1,0,0));
            m_localX = new CgPolyline(temp);
            m_renderer->init(m_localX);

            eX = new CgSceneGraphEntity();
            eX->addListObject(m_localX);
            eX->getAppearance().setObject_color(glm::vec4(0,0,1,1));
            current_Entity->addChild(eX);


            temp.pop_back();
            temp.push_back(center + glm::vec3(0,1,0));
            m_localY = new CgPolyline(temp);
            m_renderer->init(m_localY);

            eY = new CgSceneGraphEntity();
            eY->addListObject(m_localY);
            eY->getAppearance().setObject_color(glm::vec4(0,1,0,1));
            current_Entity->addChild(eY);


            temp.pop_back();
            temp.push_back(center + glm::vec3(0,0,1));
            m_localZ = new CgPolyline(temp);
            m_renderer->init(m_localZ);

            eZ = new CgSceneGraphEntity();
            eZ->addListObject(m_localZ);
            eZ->getAppearance().setObject_color(glm::vec4(1,1,0,1));
            current_Entity->addChild(eZ);


            m_renderer->redraw();

            //std::cout << "Lok Koord Zeichnen" << std::endl;
        }
        else
        {
            current_Entity->deleteLastChild();
            current_Entity->deleteLastChild();
            current_Entity->deleteLastChild();

            m_renderer->redraw();

            //std::cout << "Lok Koord löschen" << std::endl;
        }
    }

    if(e->getType() & Cg::CgRotationskoerperNormalenEvent){
        CgRotationskoerperNormalenEvent* ev = (CgRotationskoerperNormalenEvent*)e;

        if(m_rotation != NULL)
        {
            if (ev->getZeichnen())
            {
                //m_rotation->calculateFaceCenters();
                //std::vector<glm::vec3> face_centers = m_rotation->getFaceCenters();
                //m_rotation->calculateFaceNormals();
                //std::vector<glm::vec3> face_normals = m_rotation->getFaceNormals();
                m_rotation->calculateVertexNormals();
                std::vector<glm::vec3> vertex_normals = m_rotation->getVertexNormals();
                std::vector<glm::vec3> vertices = m_rotation->getVertices();

                std::vector<glm::vec3> temp;
                /*
                for (int i= 0; i < face_centers.size(); i++)
                {
                    temp.clear();
                    temp.push_back(face_centers.at(i));
                    temp.push_back(face_centers.at(i) + face_normals.at(i));

                    m_normalsRotation.push_back(new CgPolyline(temp));
                }
                */

                for(int i = 0; i < vertex_normals.size(); i++)
                {
                    temp.clear();
                    temp.push_back(vertices.at(i));
                    temp.push_back(vertices.at(i) + vertex_normals.at(i));

                    m_normalsRotation.push_back(new CgPolyline(temp));
                }

                if(!m_normalsRotation.empty())
                {
                    for(auto s : m_normalsRotation)
                    {
                        m_renderer->init(s);
                        e4->addListObject(s);
                    }
                }

                std::cout << "Normalen gezeichnet" << std::endl;
            } else {
                m_normalsRotation.clear();
                while(!e4->getList_of_objects().empty())
                {
                    e4->deleteLastListOfObject();
                }
                std::cout << "Normalen gelöscht" << std::endl;
            }

            m_renderer->redraw();
        }
    }

    if(e->getType() & Cg::CgRotationskoerperErstellenEvent){
        CgRotationskoerperErstellenEvent* ev = (CgRotationskoerperErstellenEvent*)e;

        /*
        for(glm::vec3 s : m_polyline->getVertices())
        {
            std::cout << glm::to_string(s) << std::endl;
        }
        */

        if(m_polyline != NULL)
        {
            delete m_rotation;
            m_rotation = new CgRotation(m_polyline->getVertices(), ev->getSegmente());
            m_renderer->init(m_rotation);
            e3->addListObject(m_rotation);
            m_renderer->redraw();
            std::cout << "Rotationskörper Erstellung gestartet, Anzahl Segmente: " << ev->getSegmente() << std::endl;
        }

    }

    if(e->getType() & Cg::CgSchritteResetEvent){
        CgSchritteResetEvent* ev = (CgSchritteResetEvent*)e;

        if(m_polyline != NULL)
        {
            auto id = m_polyline->getID();
            delete m_polyline;
            m_polyline = new CgPolyline(id);
            m_renderer->init(m_polyline);
            m_renderer->redraw();

            std::cout << "Reset ausgeführt" << std::endl;
        }

    }

    if(e->getType() & Cg::CgSchritteAusfuehrenEvent){
        CgSchritteAusfuehrenEvent* ev = (CgSchritteAusfuehrenEvent*)e;

        if(m_polyline != NULL)
        {
            m_polyline->startLaneRiesenfeldAlgo(ev->getSchritte());
            m_renderer->init(m_polyline);
            m_renderer->redraw();
        }
        /*
        for(glm::vec3 s : m_polyline->getVertices())
        {
            std::cout << glm::to_string(s) << std::endl;
        }
        */
        //std::cout << "Schritte ausgeführt: " << ev->getSchritte() << std::endl;
    }

    if(e->getType() & Cg::CgColorChangeEvent){
        CgColorChangeEvent* ev = (CgColorChangeEvent*)e;

        //m_renderer->setUniformValue("mycolor",glm::vec4((double)ev->red()/255,(double)ev->green()/255,(double)ev->blue()/255, 1.0));
        //iterate_graph(graph->getRoot(), glm::vec3((double)ev->red()/255,(double)ev->green()/255,(double)ev->blue()/255));

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
        //std::cout << *ev <<std::endl;


        if(ev->text()=="x")
        {
            glm::vec3 center;
            if(current_Entity->getList_of_objects().empty())
            {
                current_Entity->getChildren().at(0)->calculateCenter();
                center = current_Entity->getChildren().at(0)->getCenter();
            }
            else
            {
                current_Entity->calculateCenter();
                center = current_Entity->getCenter();
            }

            translate_obj(current_Entity, center);
            rotate_obj(current_Entity, glm::vec3(1,0,0), M_PI/16);
            translate_obj(current_Entity, center * glm::vec3(-1,-1,-1));
            m_renderer->redraw();
        }
        if(ev->text()=="y")
        {
            glm::vec3 center;
            if(current_Entity->getList_of_objects().empty())
            {
                current_Entity->getChildren().at(0)->calculateCenter();
                center = current_Entity->getChildren().at(0)->getCenter();
            }
            else
            {
                current_Entity->calculateCenter();
                center = current_Entity->getCenter();
            }

            translate_obj(current_Entity, center);
            rotate_obj(current_Entity, glm::vec3(0,1,0), M_PI/16);
            translate_obj(current_Entity, center * glm::vec3(-1,-1,-1));
            m_renderer->redraw();
        }
        if(ev->text()=="z")
        {
            glm::vec3 center;
            if(current_Entity->getList_of_objects().empty())
            {
                current_Entity->getChildren().at(0)->calculateCenter();
                center = current_Entity->getChildren().at(0)->getCenter();
            }
            else
            {
                current_Entity->calculateCenter();
                center = current_Entity->getCenter();
            }

            translate_obj(current_Entity, center);
            rotate_obj(current_Entity, glm::vec3(0,0,1), M_PI/16);
            translate_obj(current_Entity, center * glm::vec3(-1,-1,-1));
            m_renderer->redraw();
        }
        if(ev->text()=="+")
        {
            //            glm::mat4 scalemat = glm::mat4(1.);
            //            scalemat = glm::scale(scalemat,glm::vec3(1.2,1.2,1.2));
            //            m_current_transformation=m_current_transformation*scalemat;
            //            m_renderer->redraw();

            scale_obj(current_Entity, glm::vec3(1.5));
            m_renderer->redraw();
        }
        if(ev->text()=="-")
        {
            //            glm::mat4 scalemat = glm::mat4(1.);
            //            scalemat = glm::scale(scalemat,glm::vec3(0.8,0.8,0.8));

            //            m_current_transformation=m_current_transformation*scalemat;

            //            m_renderer->redraw();

            scale_obj(current_Entity, glm::vec3(0.666666667));
            m_renderer->redraw();
        }
        if(ev->text()=="n")
        {
            count++;

            if(count == graph->getListOfEntitys().size())
            {
                count = 0;
            }
            if(count == 0)
            {
                graph->getListOfEntitys().at(graph->getListOfEntitys().size()-1)->getAppearance().setObject_color(old_color);
            }
            else
            {
                graph->getListOfEntitys().at(count-1)->getAppearance().setObject_color(old_color);
            }

            old_color = glm::vec4(graph->getListOfEntitys().at(count)->getAppearance().getObject_color(),1);

            graph->getListOfEntitys().at(count)->getAppearance().setObject_color(glm::vec4(1,0,0,1));

            current_Entity = graph->getListOfEntitys().at(count);

            m_renderer->redraw();
            //std::cout << count << std::endl;
            std::cout << count << ": " << current_Entity->getName() << std::endl;
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

        m_rotation->init(pos,norm,indx);
        m_renderer->init(m_rotation);
        m_renderer->redraw();
    }

    // an der Stelle an der ein Event abgearbeitet ist wird es auch gelöscht.
    delete e;


}
