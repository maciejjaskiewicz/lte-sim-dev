project(LTE-Sim)

SET(LTE_SIM_SRC
    ${PROJECT_SOURCE_DIR}/load-parameters.h
    ${PROJECT_SOURCE_DIR}/LTE-Sim.h
    ${PROJECT_SOURCE_DIR}/channel/LteChannel.cpp
    ${PROJECT_SOURCE_DIR}/channel/LteChannel.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/3gpp-downlin-channel-realization.cpp
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/3gpp-downlin-channel-realization.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/channel-realization-helper.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/channel-realization.cpp
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/channel-realization.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/fast-fading-trace.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/jakes_model/multipath_v0_M10.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/jakes_model/multipath_v0_M12.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/jakes_model/multipath_v0_M6.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/jakes_model/multipath_v0_M8.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/jakes_model/multipath_v120_M10.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/jakes_model/multipath_v120_M12.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/jakes_model/multipath_v120_M6.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/jakes_model/multipath_v120_M8.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/jakes_model/multipath_v3_M10.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/jakes_model/multipath_v3_M12.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/jakes_model/multipath_v3_M6.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/jakes_model/multipath_v3_M8.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/jakes_model/multipath_v30_M10.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/jakes_model/multipath_v30_M12.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/jakes_model/multipath_v30_M6.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/jakes_model/multipath_v30_M8.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_PedA_speed_0.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_PedA_speed_120.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_PedA_speed_150.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_PedA_speed_200.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_PedA_speed_250.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_PedA_speed_3.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_PedA_speed_30.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_PedA_speed_300.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_PedA_speed_350.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_PedB_speed_0.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_PedB_speed_120.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_PedB_speed_150.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_PedB_speed_200.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_PedB_speed_250.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_PedB_speed_3.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_PedB_speed_30.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_PedB_speed_300.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_PedB_speed_350.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_VehA_speed_0.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_VehA_speed_120.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_VehA_speed_150.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_VehA_speed_200.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_VehA_speed_250.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_VehA_speed_3.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_VehA_speed_30.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_VehA_speed_300.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_VehA_speed_350.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_VehB_speed_0.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_VehB_speed_120.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_VehB_speed_150.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_VehB_speed_200.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_VehB_speed_250.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_VehB_speed_3.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_VehB_speed_30.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_VehB_speed_300.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/FastFadingRealization/zheng_model/fast-fading_VehB_speed_350.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/femtocell-urban-area-channel-realization.cpp
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/femtocell-urban-area-channel-realization.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/macrocell-rural-area-channel-realization.cpp
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/macrocell-rural-area-channel-realization.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/macrocell-sub-urban-area-channel-realization.cpp
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/macrocell-sub-urban-area-channel-realization.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/macrocell-urban-area-channel-realization.cpp
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/macrocell-urban-area-channel-realization.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/microcell-area-channel-realization.cpp
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/microcell-area-channel-realization.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/propagation-loss-model.cpp
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/propagation-loss-model.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/shadowing-trace.h
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/winner-downlink-channel-realization.cpp
    ${PROJECT_SOURCE_DIR}/channel/propagation-model/winner-downlink-channel-realization.h
    ${PROJECT_SOURCE_DIR}/componentManagers/FrameManager.cpp
    ${PROJECT_SOURCE_DIR}/componentManagers/FrameManager.h
    ${PROJECT_SOURCE_DIR}/componentManagers/NetworkManager.cpp
    ${PROJECT_SOURCE_DIR}/componentManagers/NetworkManager.h
    ${PROJECT_SOURCE_DIR}/componentManagers/TDDConfiguration.h
    ${PROJECT_SOURCE_DIR}/core/cartesianCoodrdinates/CartesianCoordinates.cpp
    ${PROJECT_SOURCE_DIR}/core/cartesianCoodrdinates/CartesianCoordinates.h
    ${PROJECT_SOURCE_DIR}/core/eventScheduler/calendar.cpp
    ${PROJECT_SOURCE_DIR}/core/eventScheduler/calendar.h
    ${PROJECT_SOURCE_DIR}/core/eventScheduler/event.cpp
    ${PROJECT_SOURCE_DIR}/core/eventScheduler/event.h
    ${PROJECT_SOURCE_DIR}/core/eventScheduler/make-event.h
    ${PROJECT_SOURCE_DIR}/core/idealMessages/ideal-control-messages.cc
    ${PROJECT_SOURCE_DIR}/core/idealMessages/ideal-control-messages.h
    ${PROJECT_SOURCE_DIR}/core/spectrum/bandwidth-manager.cpp
    ${PROJECT_SOURCE_DIR}/core/simulation/Simulation.h
    ${PROJECT_SOURCE_DIR}/core/simulation/Simulation.cpp
    ${PROJECT_SOURCE_DIR}/core/spectrum/bandwidth-manager.h
    ${PROJECT_SOURCE_DIR}/core/spectrum/transmitted-signal.cpp
    ${PROJECT_SOURCE_DIR}/core/spectrum/transmitted-signal.h
    ${PROJECT_SOURCE_DIR}/core/Core.h
    ${PROJECT_SOURCE_DIR}/core/main.h
    ${PROJECT_SOURCE_DIR}/device/CqiManager/cqi-manager.cpp
    ${PROJECT_SOURCE_DIR}/device/CqiManager/cqi-manager.h
    ${PROJECT_SOURCE_DIR}/device/CqiManager/fullband-cqi-manager.cpp
    ${PROJECT_SOURCE_DIR}/device/CqiManager/fullband-cqi-manager.h
    ${PROJECT_SOURCE_DIR}/device/CqiManager/wideband-cqi-manager.cpp
    ${PROJECT_SOURCE_DIR}/device/CqiManager/wideband-cqi-manager.h
    ${PROJECT_SOURCE_DIR}/device/ENodeB.cpp
    ${PROJECT_SOURCE_DIR}/device/ENodeB.h
    ${PROJECT_SOURCE_DIR}/device/Gateway.cpp
    ${PROJECT_SOURCE_DIR}/device/Gateway.h
    ${PROJECT_SOURCE_DIR}/device/HeNodeB.cpp
    ${PROJECT_SOURCE_DIR}/device/HeNodeB.h
    ${PROJECT_SOURCE_DIR}/device/IPClassifier/Classifier.cpp
    ${PROJECT_SOURCE_DIR}/device/IPClassifier/Classifier.h
    ${PROJECT_SOURCE_DIR}/device/IPClassifier/ClassifierParameters.cpp
    ${PROJECT_SOURCE_DIR}/device/IPClassifier/ClassifierParameters.h
    ${PROJECT_SOURCE_DIR}/device/NetworkNode.cpp
    ${PROJECT_SOURCE_DIR}/device/NetworkNode.h
    ${PROJECT_SOURCE_DIR}/device/UserEquipment.cpp
    ${PROJECT_SOURCE_DIR}/device/UserEquipment.h
    ${PROJECT_SOURCE_DIR}/flows/application/application-sink.cpp
    ${PROJECT_SOURCE_DIR}/flows/application/application-sink.h
    ${PROJECT_SOURCE_DIR}/flows/application/Application.cpp
    ${PROJECT_SOURCE_DIR}/flows/application/Application.h
    ${PROJECT_SOURCE_DIR}/flows/application/CBR.cpp
    ${PROJECT_SOURCE_DIR}/flows/application/CBR.h
    ${PROJECT_SOURCE_DIR}/flows/application/InfiniteBuffer.cpp
    ${PROJECT_SOURCE_DIR}/flows/application/InfiniteBuffer.h
    ${PROJECT_SOURCE_DIR}/flows/application/Trace/default-trace.h
    ${PROJECT_SOURCE_DIR}/flows/application/TraceBased.cpp
    ${PROJECT_SOURCE_DIR}/flows/application/TraceBased.h
    ${PROJECT_SOURCE_DIR}/flows/application/VoIP.cpp
    ${PROJECT_SOURCE_DIR}/flows/application/VoIP.h
    ${PROJECT_SOURCE_DIR}/flows/application/WEB.cpp
    ${PROJECT_SOURCE_DIR}/flows/application/WEB.h
    ${PROJECT_SOURCE_DIR}/flows/MacQueue.cpp
    ${PROJECT_SOURCE_DIR}/flows/MacQueue.h
    ${PROJECT_SOURCE_DIR}/flows/QoS/QoSForEXP.cpp
    ${PROJECT_SOURCE_DIR}/flows/QoS/QoSForEXP.h
    ${PROJECT_SOURCE_DIR}/flows/QoS/QoSForFLS.cpp
    ${PROJECT_SOURCE_DIR}/flows/QoS/QoSForFLS.h
    ${PROJECT_SOURCE_DIR}/flows/QoS/QoSForM_LWDF.cpp
    ${PROJECT_SOURCE_DIR}/flows/QoS/QoSForM_LWDF.h
    ${PROJECT_SOURCE_DIR}/flows/QoS/QoSParameters.cpp
    ${PROJECT_SOURCE_DIR}/flows/QoS/QoSParameters.h
    ${PROJECT_SOURCE_DIR}/flows/radio-bearer-instance.cpp
    ${PROJECT_SOURCE_DIR}/flows/radio-bearer-instance.h
    ${PROJECT_SOURCE_DIR}/flows/radio-bearer-sink.cpp
    ${PROJECT_SOURCE_DIR}/flows/radio-bearer-sink.h
    ${PROJECT_SOURCE_DIR}/flows/radio-bearer.cpp
    ${PROJECT_SOURCE_DIR}/flows/radio-bearer.h
    ${PROJECT_SOURCE_DIR}/flows/ApplicationFactory.h
    ${PROJECT_SOURCE_DIR}/load-parameters.h
    ${PROJECT_SOURCE_DIR}/mobility/ConstantPosition.cpp
    ${PROJECT_SOURCE_DIR}/mobility/ConstantPosition.h
    ${PROJECT_SOURCE_DIR}/mobility/Manhattan.cpp
    ${PROJECT_SOURCE_DIR}/mobility/Manhattan.h
    ${PROJECT_SOURCE_DIR}/mobility/Mobility.cpp
    ${PROJECT_SOURCE_DIR}/mobility/Mobility.h
    ${PROJECT_SOURCE_DIR}/mobility/RandomDirection.cpp
    ${PROJECT_SOURCE_DIR}/mobility/RandomDirection.h
    ${PROJECT_SOURCE_DIR}/mobility/RandomWalk.cpp
    ${PROJECT_SOURCE_DIR}/mobility/RandomWalk.h
    ${PROJECT_SOURCE_DIR}/mobility/RandomWaypoint.cpp
    ${PROJECT_SOURCE_DIR}/mobility/RandomWaypoint.h
    ${PROJECT_SOURCE_DIR}/networkTopology/5x5ApartmentGrid.cpp
    ${PROJECT_SOURCE_DIR}/networkTopology/5x5ApartmentGrid.h
    ${PROJECT_SOURCE_DIR}/networkTopology/Building.cpp
    ${PROJECT_SOURCE_DIR}/networkTopology/Building.h
    ${PROJECT_SOURCE_DIR}/networkTopology/Cell.cpp
    ${PROJECT_SOURCE_DIR}/networkTopology/Cell.h
    ${PROJECT_SOURCE_DIR}/networkTopology/DualStripe.cpp
    ${PROJECT_SOURCE_DIR}/networkTopology/DualStripe.h
    ${PROJECT_SOURCE_DIR}/networkTopology/Femtocell.cpp
    ${PROJECT_SOURCE_DIR}/networkTopology/Femtocell.h
    ${PROJECT_SOURCE_DIR}/networkTopology/Street.cpp
    ${PROJECT_SOURCE_DIR}/networkTopology/Street.h
    ${PROJECT_SOURCE_DIR}/phy/BLERTrace/BLERvsSINR_15CQI_AWGN.h
    ${PROJECT_SOURCE_DIR}/phy/BLERTrace/BLERvsSINR_15CQI_TU.h
    ${PROJECT_SOURCE_DIR}/phy/enb-lte-phy.cpp
    ${PROJECT_SOURCE_DIR}/phy/enb-lte-phy.h
    ${PROJECT_SOURCE_DIR}/phy/error-model.cpp
    ${PROJECT_SOURCE_DIR}/phy/error-model.h
    ${PROJECT_SOURCE_DIR}/phy/henb-lte-phy.cpp
    ${PROJECT_SOURCE_DIR}/phy/henb-lte-phy.h
    ${PROJECT_SOURCE_DIR}/phy/interference.cpp
    ${PROJECT_SOURCE_DIR}/phy/interference.h
    ${PROJECT_SOURCE_DIR}/phy/lte-phy.cpp
    ${PROJECT_SOURCE_DIR}/phy/lte-phy.h
    ${PROJECT_SOURCE_DIR}/phy/simple-error-model.cpp
    ${PROJECT_SOURCE_DIR}/phy/simple-error-model.h
    ${PROJECT_SOURCE_DIR}/phy/ue-lte-phy.cpp
    ${PROJECT_SOURCE_DIR}/phy/ue-lte-phy.h
    ${PROJECT_SOURCE_DIR}/phy/wideband-cqi-eesm-error-model.cpp
    ${PROJECT_SOURCE_DIR}/phy/wideband-cqi-eesm-error-model.h
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/AMCModule.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/AMCModule.h
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/enb-mac-entity.cc
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/enb-mac-entity.h
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/harq-manager.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/harq-manager.h
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/henb-mac-entity.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/henb-mac-entity.h
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/mac-entity.cc
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/mac-entity.h
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/delay-edd-rule-downlink-packet-scheduler.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/delay-edd-rule-downlink-packet-scheduler.h
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/dl-exp-packet-scheduler.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/dl-exp-packet-scheduler.h
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/dl-fls-packet-scheduler.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/dl-fls-packet-scheduler.h
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/dl-mlwdf-packet-scheduler.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/dl-mlwdf-packet-scheduler.h
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/dl-pf-packet-scheduler.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/dl-pf-packet-scheduler.h
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/downlink-packet-scheduler.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/downlink-packet-scheduler.h
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/enhanced-uplink-packet-scheduler.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/enhanced-uplink-packet-scheduler.h
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/exp-rule-downlink-packet-scheduler.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/exp-rule-downlink-packet-scheduler.h
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/log-rule-downlink-packet-scheduler.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/log-rule-downlink-packet-scheduler.h
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/mt-uplink-packet-scheduler.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/mt-uplink-packet-scheduler.h
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/mw-rule-downlink-packet-scheduler.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/mw-rule-downlink-packet-scheduler.h
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/my-sch-fair-packet-scheduler.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/my-sch-fair-packet-scheduler.h
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/packet-scheduler.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/packet-scheduler.h
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/roundrobin-uplink-packet-scheduler.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/roundrobin-uplink-packet-scheduler.h
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/uplink-packet-scheduler.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/packet-scheduler/uplink-packet-scheduler.h
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/ue-mac-entity.cc
    ${PROJECT_SOURCE_DIR}/protocolStack/mac/ue-mac-entity.h
    ${PROJECT_SOURCE_DIR}/protocolStack/nas/nas-entity.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/nas/nas-entity.h
    ${PROJECT_SOURCE_DIR}/protocolStack/packet/Header.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/packet/Header.h
    ${PROJECT_SOURCE_DIR}/protocolStack/packet/packet-burst.cc
    ${PROJECT_SOURCE_DIR}/protocolStack/packet/packet-burst.h
    ${PROJECT_SOURCE_DIR}/protocolStack/packet/Packet.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/packet/Packet.h
    ${PROJECT_SOURCE_DIR}/protocolStack/packet/PacketTAGs.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/packet/PacketTAGs.h
    ${PROJECT_SOURCE_DIR}/protocolStack/packet/PacketAttributes.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/packet/PacketAttributes.h
    ${PROJECT_SOURCE_DIR}/protocolStack/pdcp/pdcp-entity.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/pdcp/pdcp-entity.h
    ${PROJECT_SOURCE_DIR}/protocolStack/protocol-stack.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/protocol-stack.h
    ${PROJECT_SOURCE_DIR}/protocolStack/protocols/TransportProtocol.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/protocols/TransportProtocol.h
    ${PROJECT_SOURCE_DIR}/protocolStack/rlc/am-rlc-entity.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/rlc/am-rlc-entity.h
    ${PROJECT_SOURCE_DIR}/protocolStack/rlc/am-state-variables.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/rlc/am-state-variables.h
    ${PROJECT_SOURCE_DIR}/protocolStack/rlc/amd-record.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/rlc/amd-record.h
    ${PROJECT_SOURCE_DIR}/protocolStack/rlc/rlc-entity.cc
    ${PROJECT_SOURCE_DIR}/protocolStack/rlc/rlc-entity.h
    ${PROJECT_SOURCE_DIR}/protocolStack/rlc/tm-rlc-entity.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/rlc/tm-rlc-entity.h
    ${PROJECT_SOURCE_DIR}/protocolStack/rlc/um-rlc-entity.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/rlc/um-rlc-entity.h
    ${PROJECT_SOURCE_DIR}/protocolStack/rrc/ho/handover-entity.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/rrc/ho/handover-entity.h
    ${PROJECT_SOURCE_DIR}/protocolStack/rrc/ho/ho-manager.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/rrc/ho/ho-manager.h
    ${PROJECT_SOURCE_DIR}/protocolStack/rrc/ho/position-based-ho-manager.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/rrc/ho/position-based-ho-manager.h
    ${PROJECT_SOURCE_DIR}/protocolStack/rrc/ho/power-based-ho-manager.cpp
    ${PROJECT_SOURCE_DIR}/protocolStack/rrc/ho/power-based-ho-manager.h
    ${PROJECT_SOURCE_DIR}/protocolStack/rrc/rrc-entity.cc
    ${PROJECT_SOURCE_DIR}/protocolStack/rrc/rrc-entity.h
    ${PROJECT_SOURCE_DIR}/utility/CellPosition.h
    ${PROJECT_SOURCE_DIR}/utility/ComputePathLoss.h
    ${PROJECT_SOURCE_DIR}/utility/eesm-effective-sinr.h
    ${PROJECT_SOURCE_DIR}/utility/frequency-reuse-helper.h
    ${PROJECT_SOURCE_DIR}/utility/help.h
    ${PROJECT_SOURCE_DIR}/utility/IndoorScenarios.h
    ${PROJECT_SOURCE_DIR}/utility/MultipathInterpolation.h
    ${PROJECT_SOURCE_DIR}/utility/RandomVariable.h
    ${PROJECT_SOURCE_DIR}/utility/seed.h
    ${PROJECT_SOURCE_DIR}/utility/UsersDistribution.h
    ${PROJECT_SOURCE_DIR}/utility/PacketHelper.h
    ${PROJECT_SOURCE_DIR}/output/Models/OutputModel.cpp
    ${PROJECT_SOURCE_DIR}/output/Models/OutputModel.h
    ${PROJECT_SOURCE_DIR}/output/Models/SimulationMetricsModel.cpp
    ${PROJECT_SOURCE_DIR}/output/Models/SimulationMetricsModel.h
    ${PROJECT_SOURCE_DIR}/output/OutputFactory.cpp
    ${PROJECT_SOURCE_DIR}/output/OutputFactory.h
    ${PROJECT_SOURCE_DIR}/output/SimulationMetricsCalculator.cpp
    ${PROJECT_SOURCE_DIR}/output/SimulationMetricsCalculator.h
    ${PROJECT_SOURCE_DIR}/output/CSV/CSVOutputBuilder.cpp
    ${PROJECT_SOURCE_DIR}/output/CSV/CSVOutputBuilder.h
)
source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${LTE_SIM_SRC})

add_library(${PROJECT_NAME} SHARED ${LTE_SIM_SRC})
add_library(LTE-Sim::LTE-Sim ALIAS ${PROJECT_NAME})

if (WIN32)
    target_compile_definitions(${PROJECT_NAME} PUBLIC LTE_SIM_PLATFORM_WINDOWS=1)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LTE_SIM_BUILD_DLL=1)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE LTE_SIM_ENABLE_ASSERTS=1)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
