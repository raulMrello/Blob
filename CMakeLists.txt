idf_component_register(	SRCS "common_objects.cpp" 
							"JsonParserBlob.cpp"
						INCLUDE_DIRS "."
						REQUIRES mbed_api_esp32 json 
						AstCalendar
						AMManager
						SysManager
						MQTTClient
						HMIManager
						ShuckoManager
						MennekesManager
						EVStateMachine
						RequestsManager
						SchedulerManager
						ModulatorManager
						Stm32Updater
						OCPPManager
						ModbusMap
						SolarManager
						WSClient
						CANBridge
						EmbeddedWeb
						)