/*
 * JsonParserBlob_UserConfig.h
 *
 *  Created on: Aug 2019
 *      Author: raulMrello
 *
 *
 * Este archivo de cabecera es externo al proyecto y debe definir las diferentes claves que habilitan o deshabilitan
 * porciones de c�digo. Puesto que este m�dulo integra objetos de diferentes proyectos (AstCalendar, AMManager,
 * LightManager, etc...) es necesario habilitar �nicamente aquellos componentes que se quiera utilizar, de forma que
 * la compilaci�n pueda llevarse a cabo en diferentes plataformas o proyectos.
 *
 * Las claves que debe definir este archivo son:
 *
 * JsonParser_AstCalendar_Enabled
 * JsonParser_AMManager_Enabled
 * JsonParser_LightManager_Enabled
 * JsonParser_FwUpdater_Enabled
 * JsonParser_MQTTClient_Enabled
 * JsonParser_HMIManager_Enabled
 * JsonParser_BlufiManager_Enabled
 * JsonParser_ServerSocket_Enabled
 *
 */

 
#ifndef JSONPARSERBLOB_USERCONFIG_Chargers_H
#define JSONPARSERBLOB_USERCONFIG_Chargers_H

/**
 * Este archivo de cabecera es externo al proyecto y debe definir las diferentes claves que habilitan o deshabilitan
 * porciones de c�digo. Puesto que este m�dulo integra objetos de diferentes proyectos (AstCalendar, AMManager,
 * LightManager, etc...) es necesario habilitar �nicamente aquellos componentes que se quiera utilizar, de forma que
 * la compilaci�n pueda llevarse a cabo en diferentes plataformas o proyectos.
 *
 * Las claves que debe definir este archivo son:
 *
 * JsonParser_AstCalendar_Enabled
 * JsonParser_AMManager_Enabled
 * JsonParser_SysManager_Enabled
 * JsonParser_LightManager_Enabled
 * JsonParser_FwUpdater_Enabled
 * JsonParser_MQTTClient_Enabled
 * JsonParser_HMIManager_Enabled
 * JsonParser_BlufiManager_Enabled
 * JsonParser_ServerSocket_Enabled
 *
 */

// #define JsonParser_SysManager_Enabled
#define JsonParser_SysManager_Panels_Enabled
#define JsonParser_MQTTClient_Enabled
// #define JsonParser_HMIManager_Enabled



#endif
