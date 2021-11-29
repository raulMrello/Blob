/*
 * common_objects.h
 *
 *  Created on: Mar 2019
 *      Author: raulMrello
 *
 *	Objetos JSON e prop�sito general
 */
 
#ifndef COMMON_OBJECTS_
#define COMMON_OBJECTS_

#include <cstdint>
#include <type_traits>
#include "cJSON.h"

#define MWIFI_ADDR_LEN              6
#define MWIFI_ADDR_NONE         {0x0, 0x0, 0x0, 0x0, 0x0, 0x0}
#define MWIFI_ADDR_ROOT         {0xFF, 0x0, 0x0, 0x1, 0x0, 0x0}
#define MWIFI_ADDR_ANY          {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF} /**< All node in the mesh network */
#define MWIFI_ADDR_BROADCAST    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0XFE} /**< Other node except the root */


/** Tipos de secciones de datos que se pueden leer-escribir en los objetos
 *
 */
enum ObjDataSelection {
	ObjSelectAll,   //!< ObjSelectAll 	Todo el contenido del objeto
	ObjSelectState,	//!< ObjSelectState �nicamente el estado del objeto y de los submodulos y/o elementos
	ObjSelectCfg, 	//!< ObjSelectCfg 	�nicamente la configuraci�n del objeto y de los submodulos y/o elementos
	ObjSelectAllMan,   //!< ObjSelectAllMan 	Todo el contenido del objeto sin submodulos ni elementos
	ObjSelectStateMan,	//!< ObjSelectStateMan �nicamente el estado del objeto sin submodulos ni elementos
	ObjSelectCfgMan, 	//!< ObjSelectCfgMan 	�nicamente la configuraci�n del objeto sin submodulos ni elementos
	ObjSelectAllSub, // !< ObjSelectAllSub 	Todo el contenido únicamente de los submodulos y/o elementos
	ObjSelectStateSub, // !< ObjSelectStateSub 	�nicamente la configuración de los submodulos y/o elementos
	ObjSelectCfgSub, // !< ObjSelectCfgSub 	�nicamente la configuración de los submodulos y/o elementos
	ObjSelectComm // !< ObjSelectCfgSub 	�nicamente la configuración de los submodulos y/o elementos
};


/** Objeto range:minmaxthres:double */
struct common_range_minmaxthres_double{
	double min;
	double max;
	double thres;
};


namespace JSON {

/**
 * Codifica el objeto en un JSON
 * @param obj Objeto
 * @return JSON resultante o NULL en caso de error
 */
cJSON* getJsonFromRangeMinMaxThresDouble(const common_range_minmaxthres_double& obj);


/**
 * Decodifica el mensaje JSON en un objeto
 * @param obj Recibe el objeto decodificado
 * @param json Objeto JSON a decodificar
 * @return keys Par�metros decodificados o 0 en caso de error
 */
uint32_t getRangeMinMaxThresDoubleFromJson(common_range_minmaxthres_double &obj, cJSON* json);


}	// end namespace JSON

#endif
