
ADD_LIBRARY(locators STATIC
    ApplicationFolder.cpp
    EnvironmentVarLocation.cpp
    EnvironmentVarData.cpp
    ExternalDefinition.cpp
    LocatorStrategy.cpp
    LocatorFactory.cpp
)

add_dependencies( locators os base )

target_link_libraries(
     locators
     os
     base
)

