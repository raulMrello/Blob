/*
 * common_objects.h
 *
 *  Created on: Mar 2019
 *      Author: raulMrello
 *
 *	Objetos JSON e propósito general
 */
 
#ifndef COMMON_OBJECTS_
#define COMMON_OBJECTS_

#include <cstdint>
#include <type_traits>
#include "cJSON.h"


/** Tipos de secciones de datos que se pueden leer-escribir en los objetos
 *
 */
enum ObjDataSelection {
	ObjSelectAll,   //!< ObjSelectAll 	Todo el contenido del objeto
	ObjSelectState,	//!< ObjSelectState Únicamente el estado del objeto
	ObjSelectCfg 	//!< ObjSelectCfg 	Únicamente la configuración del objeto
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
 * @return keys Parámetros decodificados o 0 en caso de error
 */
uint32_t getRangeMinMaxThresDoubleFromJson(common_range_minmaxthres_double &obj, cJSON* json);


}	// end namespace JSON

#endif
