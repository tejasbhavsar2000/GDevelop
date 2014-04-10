/** \file
 *  Game Develop
 *  2008-2014 Florian Rival (Florian.Rival@gmail.com)
 */
#include "GDCore/PlatformDefinition/Project.h"
#include "GDCore/PlatformDefinition/Platform.h"
#include "GDCore/Events/InstructionMetadata.h"
#include "GDCore/Events/EventsList.h"
#include "GDCore/Events/Event.h"
#include "GDCore/Events/Serialization.h"
#include "GDCore/Events/Instruction.h"
#include "GDCore/TinyXml/tinyxml.h"
#include "GDCore/IDE/MetadataProvider.h"
#include "GDCore/Tools/Log.h"
#include "GDCore/CommonTools.h"

using namespace std;

namespace gd
{

void EventsListSerialization::UpdateInstructionsFromGD31x(gd::Project & project, std::vector < gd::Instruction > & list, bool instructionsAreActions)
{
    for (unsigned int i = 0;i<list.size();++i)
    {
        gd::Instruction & instr = list[i];

        const gd::InstructionMetadata & metadata = instructionsAreActions ?
                                             MetadataProvider::GetActionMetadata(project.GetCurrentPlatform(), instr.GetType()) :
                                             MetadataProvider::GetConditionMetadata(project.GetCurrentPlatform(), instr.GetType());

        if (instr.GetType() == "VarScene" ||
            instr.GetType() == "VarSceneTxt" ||
            instr.GetType() == "VarGlobal" ||
            instr.GetType() == "VarGlobalTxt" ||
            instr.GetType() == "ModVarScene" ||
            instr.GetType() == "ModVarSceneTxt" ||
            instr.GetType() == "ModVarGlobal" ||
            instr.GetType() == "ModVarGlobalTxt" )
        {
            std::vector< gd::Expression > parameters = instr.GetParameters();
            if ( parameters.size() >= 1 ) parameters.erase(parameters.begin()+0);
            instr.SetParameters(parameters);
        }

        if (instr.GetType() == "VarSceneDef" ||
            instr.GetType() == "VarGlobalDef" ||
            instr.GetType() == "VarObjetDef" )
        {
            instr.SetParameter(1, gd::Expression("\""+instr.GetParameter(1).GetPlainString()+"\""));
        }

        //UpdateInstructionsFromGD31x(project, instr.GetSubInstructions(), instructionsAreActions);
    }
}

void EventsListSerialization::UpdateInstructionsFromGD2x(gd::Project & project, std::vector < gd::Instruction > & list, bool instructionsAreActions)
{
    for (unsigned int i = 0;i<list.size();++i)
    {
        gd::Instruction & instr = list[i];

        const gd::InstructionMetadata & metadata = instructionsAreActions ?
                                             MetadataProvider::GetActionMetadata(project.GetCurrentPlatform(), instr.GetType()) :
                                             MetadataProvider::GetConditionMetadata(project.GetCurrentPlatform(), instr.GetType());

        //Specific updates for some instructions
        if ( instr.GetType() == "LinkedObjects::LinkObjects" || instr.GetType() == "LinkedObjects::RemoveLinkBetween" )
        {
            instr.SetParameter(1, instr.GetParameter(3));
            instr.SetParameter(2, instr.GetParameter(4));
        }
        else if (instr.GetType() == "LinkedObjects::RemoveAllLinksOf")
        {
            instr.SetParameter(1, instr.GetParameter(2));
        }
        else if (instr.GetType() == "LinkedObjects::PickObjectsLinkedTo")
        {
            instr.SetParameter(1, instr.GetParameter(5));
            instr.SetParameter(2, instr.GetParameter(3));
        }
        else if (instr.GetType() == "PhysicsAutomatism::AddRevoluteJointBetweenObjects")
        {
            instr.SetParameter(4, instr.GetParameter(5));
            instr.SetParameter(5, instr.GetParameter(6));
        }
        else if (instr.GetType() == "PhysicsAutomatism::AddRevoluteJointBetweenObjects")
        {
            instr.SetParameter(4, instr.GetParameter(5));
            instr.SetParameter(5, instr.GetParameter(6));
        }
        else if (instr.GetType() == "FixCamera" || instr.GetType() == "CentreCamera")
        {
            std::vector< gd::Expression > parameters = instr.GetParameters();
            if ( parameters.size() >= 3 ) parameters.erase(parameters.begin()+2);
            instr.SetParameters(parameters);
        }
        else if (instr.GetType() == "AjoutObjConcern" || instr.GetType() == "AjoutHasard")
        {
            instr.SetParameter(1, instr.GetParameter(3));
        }
        else if (instr.GetType() == "SeDirige" || instr.GetType() == "EstTourne" )
        {
            std::vector< gd::Expression > parameters = instr.GetParameters();
            if ( parameters.size() >= 3 ) parameters.erase(parameters.begin()+2);
            if ( parameters.size() >= 3 ) parameters.erase(parameters.begin()+2);
            instr.SetParameters(parameters);
        }
        else if (instr.GetType() == "Create")
        {
            std::vector< gd::Expression > parameters = instr.GetParameters();
            if ( parameters.size() >= 2 ) parameters.erase(parameters.begin()+1);
            if ( parameters.size() >= 2 ) parameters.erase(parameters.begin()+1);
            instr.SetParameters(parameters);
        }
        else if (instr.GetType() == "CreateByName")
        {
            std::vector< gd::Expression > parameters = instr.GetParameters();
            if ( parameters.size() >= 2 ) parameters.erase(parameters.begin()+1);
            instr.SetParameters(parameters);
        }
        else if (instr.GetType() == "NbObjet")
        {
            std::vector< gd::Expression > parameters = instr.GetParameters();
            if ( parameters.size() >= 2 ) parameters.erase(parameters.begin()+1);
            instr.SetParameters(parameters);
        }
        else if (instr.GetType() == "Distance")
        {
            std::vector< gd::Expression > parameters = instr.GetParameters();
            if ( parameters.size() >= 3 ) parameters.erase(parameters.begin()+2);
            if ( parameters.size() >= 3 ) parameters.erase(parameters.begin()+2);
            if ( parameters.size() >= 4 && (parameters[3].GetPlainString() == ">=" || parameters[3].GetPlainString() == ">") )
            {
                instr.SetInverted(true);
            }
            else
            {
                instr.SetInverted(false);
            }
            instr.SetParameters(parameters);
        }

        //Common updates for some parameters
        const std::vector< gd::Expression > & parameters = instr.GetParameters();
        for (unsigned int j = 0;j<parameters.size() && j<metadata.parameters.size();++j)
        {
            if ( metadata.parameters[j].type == "relationalOperator" ||
                 metadata.parameters[j].type == "operator" )
            {
                if ( j == parameters.size()-1 )
                {
                    std::cout << "ERROR: No more parameters after a [relational]operator when trying to update an instruction from GD2.x";
                }
                else
                {
                    //Exchange parameters
                    std::string op = parameters[j+1].GetPlainString();
                    instr.SetParameter(j+1, parameters[j] );
                    instr.SetParameter(j, gd::Expression(op));
                }
            }
        }

        //UpdateInstructionsFromGD2x(project, instr.GetSubInstructions(), instructionsAreActions);
    }
}

void EventsListSerialization::LoadEventsFromXml(gd::Project & project, EventsList & list, const TiXmlElement * events)
{
    const TiXmlElement * eventElem = events->FirstChildElement();
    while ( eventElem )
    {
        string type;
        if ( eventElem->FirstChildElement( "Type" ) && eventElem->FirstChildElement( "Type" )->Attribute( "value" ))
            type = eventElem->FirstChildElement( "Type" )->Attribute( "value" );

        gd::BaseEventSPtr event = project.CreateEvent(type);
        if ( event != boost::shared_ptr<gd::BaseEvent>())
        {
            event->LoadFromXml(project, eventElem);
        }
        else
        {
            gd::LogWarning("Unknown event of type " + type);
            event = boost::shared_ptr<gd::BaseEvent>(new EmptyEvent);
        }

        if ( eventElem->Attribute( "disabled" ) != NULL ) { if ( string(eventElem->Attribute( "disabled" )) == "true" ) event->SetDisabled(); }
        if ( eventElem->Attribute( "folded" ) != NULL ) { event->folded = ( string(eventElem->Attribute( "folded" )) == "true" ); }

        list.InsertEvent(*event, list.GetEventsCount());

        eventElem = eventElem->NextSiblingElement();
    }
}

void EventsListSerialization::SaveEventsToXml(const EventsList & list, TiXmlElement * events)
{
    for ( unsigned int j = 0;j < list.size();j++ )
    {
        const gd::BaseEvent & event = list.GetEvent(j);
        TiXmlElement * eventElem = new TiXmlElement( "Event" );

        eventElem->SetAttribute( "disabled", event.IsDisabled() ? "true" : "false" );
        eventElem->SetAttribute( "folded", event.folded ? "true" : "false" );
        events->LinkEndChild( eventElem );

        TiXmlElement * type = new TiXmlElement( "Type" );
        eventElem->LinkEndChild( type );
        type->SetAttribute( "value", event.GetType().c_str() );

        event.SaveToXml(eventElem);
    }
}

using namespace std;


void gd::EventsListSerialization::OpenConditions(gd::Project & project, vector < gd::Instruction > & conditions, const TiXmlElement * elem)
{
    if (elem == NULL) return;
    const TiXmlElement * elemConditions = elem->FirstChildElement();

    //Passage en revue des conditions
    while ( elemConditions )
    {
        gd::Instruction instruction;

        //Read type and infos
        const TiXmlElement *elemPara = elemConditions->FirstChildElement( "Type" );
        if ( elemPara != NULL )
        {
            instruction.SetType( elemPara->Attribute( "value" ) != NULL ? elemPara->Attribute( "value" ) : "");
            instruction.SetInverted( (elemPara->Attribute( "Contraire" ) != NULL) && (string(elemPara->Attribute( "Contraire" )) == "true") );
        }

        //Read parameters
        vector < gd::Expression > parameters;
        elemPara = elemConditions->FirstChildElement("Parametre");
        while ( elemPara )
        {
            if ( elemPara->Attribute( "value" ) != NULL ) parameters.push_back( gd::Expression(elemPara->Attribute( "value" )) );
            elemPara = elemPara->NextSiblingElement("Parametre");
        }
        instruction.SetParameters( parameters );

        //Read sub conditions
        if ( elemConditions->FirstChildElement( "SubConditions" ) != NULL )
            OpenConditions(project, instruction.GetSubInstructions(), elemConditions->FirstChildElement( "SubConditions" ));

        conditions.push_back( instruction );

        elemConditions = elemConditions->NextSiblingElement();
    }

    if ( project.GetLastSaveGDMajorVersion() < 3 ||
         (project.GetLastSaveGDMajorVersion() == 3 && project.GetLastSaveGDMinorVersion() <= 1 ) )
        UpdateInstructionsFromGD31x(project, conditions, false);

    if ( project.GetLastSaveGDMajorVersion() < 3 )
        UpdateInstructionsFromGD2x(project, conditions, false);
}

void gd::EventsListSerialization::OpenActions(gd::Project & project, vector < gd::Instruction > & actions, const TiXmlElement * elem)
{
    if (elem == NULL) return;
    const TiXmlElement * elemActions = elem->FirstChildElement();

    //Passage en revue des actions
    while ( elemActions )
    {
        gd::Instruction instruction;

        //Read type and info
        const TiXmlElement *elemPara = elemActions->FirstChildElement( "Type" );
        if ( elemPara != NULL )
        {
            if (elemPara->Attribute( "value" ) != NULL) instruction.SetType( elemPara->Attribute( "value" ));
        }

        //Read parameters
        vector < gd::Expression > parameters;
        elemPara = elemActions->FirstChildElement("Parametre");
        while ( elemPara )
        {
            if (elemPara->Attribute( "value" ) != NULL) parameters.push_back( gd::Expression(elemPara->Attribute( "value" )) );
            elemPara = elemPara->NextSiblingElement("Parametre");
        }
        instruction.SetParameters(parameters);

        //Read sub actions
        if ( elemActions->FirstChildElement( "SubActions" ) != NULL )
            OpenActions(project, instruction.GetSubInstructions(), elemActions->FirstChildElement( "SubActions" ));

        actions.push_back(instruction);
        elemActions = elemActions->NextSiblingElement();
    }

    if ( project.GetLastSaveGDMajorVersion() < 3 ||
         (project.GetLastSaveGDMajorVersion() == 3 && project.GetLastSaveGDMinorVersion() <= 1 ) )
        UpdateInstructionsFromGD31x(project, actions, true);

    if ( project.GetLastSaveGDMajorVersion() < 3 )
        UpdateInstructionsFromGD2x(project, actions, true);
}

void gd::EventsListSerialization::SaveActions(const vector < gd::Instruction > & list, TiXmlElement * actions)
{
    for ( unsigned int k = 0;k < list.size();k++ )
    {
        //Pour chaque condition
        TiXmlElement * action;

        action = new TiXmlElement( "Action" );
        actions->LinkEndChild( action );

        //Le type
        TiXmlElement * typeAction;
        typeAction = new TiXmlElement( "Type" );
        action->LinkEndChild( typeAction );

        typeAction->SetAttribute( "value", list[k].GetType().c_str() );


        //Les autres paramètres
        for ( unsigned int l = 0;l < list[k].GetParameters().size();l++ )
        {
            TiXmlElement * Parametre = new TiXmlElement( "Parametre" );
            action->LinkEndChild( Parametre );
            Parametre->SetAttribute( "value", list[k].GetParameter( l ).GetPlainString().c_str() );
        }

        //Sub instructions
        if ( !list[k].GetSubInstructions().empty() )
        {
            TiXmlElement * subActions = new TiXmlElement( "SubActions" );
            action->LinkEndChild(subActions);
            SaveActions(list[k].GetSubInstructions() , subActions);
        }
    }
}

void gd::EventsListSerialization::SaveConditions(const vector < gd::Instruction > & list, TiXmlElement * conditions)
{
    for ( unsigned int k = 0;k < list.size();k++ )
    {
        //Pour chaque condition
        TiXmlElement * condition = new TiXmlElement( "Condition" );
        conditions->LinkEndChild( condition );

        //Le type
        TiXmlElement * typeCondition = new TiXmlElement( "Type" );
        condition->LinkEndChild( typeCondition );

        typeCondition->SetAttribute( "value", list[k].GetType().c_str() );
        if ( list[k].IsInverted() ) { typeCondition->SetAttribute( "Contraire", "true" ); }
        else { typeCondition->SetAttribute( "Contraire", "false" ); }

        //Les autres paramètres
        for ( unsigned int l = 0;l < list[k].GetParameters().size();l++ )
        {
            TiXmlElement * Parametre = new TiXmlElement( "Parametre" );
            condition->LinkEndChild( Parametre );
            Parametre->SetAttribute( "value", list[k].GetParameter( l ).GetPlainString().c_str() );
        }

        //Sub instructions
        if ( !list[k].GetSubInstructions().empty() )
        {
            TiXmlElement * subConditions = new TiXmlElement( "SubConditions" );
            condition->LinkEndChild(subConditions);
            SaveConditions(list[k].GetSubInstructions(), subConditions);
        }
    }
}

}
