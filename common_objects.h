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


/** UIDs */
#define UID_COMMON_RANGE_MINMAXTHRES_DOUBLE(vers)	(uint32_t)(0x00010000 | ((uint32_t)vers << 20))



/** Objeto range:minmaxthres:double */
struct common_range_minmaxthres_double{
	uint32_t uid;
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
