#!/bin/bash

# ------------------------------------------------------------------------------
# Generates a minimal Simplicity Studio wrapper project
# The wrapper project only contains metadata and points to your manual source tree.
#
# This avoids auto-generated code and satisfies:
# - Studio for build/flash/debug only
# - VS Code as main development environment
#
# Output: studio_project/ (import into Simplicity Studio)
# ------------------------------------------------------------------------------

PROJECT_DIR="studio_project"
SRC_ROOT=".."   # point Studio to the real source tree

DEVICE="EFR32FG25A121F1152IM56"
PROJECT_NAME="WiSUN_BR_NR_ManualProject"

echo "Generating Simplicity Studio wrapper project..."

# ------------------------------------------------------------------------------
# Create folder structure
# ------------------------------------------------------------------------------
mkdir -p $PROJECT_DIR
mkdir -p $PROJECT_DIR/.project
mkdir -p $PROJECT_DIR/.settings

# ------------------------------------------------------------------------------
# .project file for Eclipse/Simplicity Studio
# ------------------------------------------------------------------------------
cat > $PROJECT_DIR/.project <<EOF
<?xml version="1.0" encoding="UTF-8"?>
<projectDescription>
    <name>$PROJECT_NAME</name>
    <comment>Manual source tree wrapper for Wi-SUN BR/NR project</comment>
    <projects>
    </projects>
    <buildSpec>
    </buildSpec>
    <natures>
        <nature>org.eclipse.cdt.core.cnature</nature>
        <nature>org.eclipse.cdt.core.ccnature</nature>
    </natures>
</projectDescription>
EOF

# ------------------------------------------------------------------------------
# .cproject file to disable Studio auto-generation
# ------------------------------------------------------------------------------
cat > $PROJECT_DIR/.cproject <<EOF
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<cproject storage_type_id="org.eclipse.cdt.core.XmlProjectDescriptionStorage">
    <storageModule moduleId="org.eclipse.cdt.core.settings" />
    <storageModule moduleId="org.eclipse.cdt.core.language.mapping"/>
    <storageModule moduleId="cdtBuildSystem" />
    <storageModule moduleId="org.eclipse.cdt.core.externalSettings"/>
</cproject>
EOF

# ------------------------------------------------------------------------------
# Simplicity Studio .project.properties (IMPORTANT)
# This tells Studio:
# - Which device
# - That this is a "Makefile Project"
# - DO NOT generate code
# ------------------------------------------------------------------------------
cat > $PROJECT_DIR/.project.properties <<EOF
project.name=$PROJECT_NAME
com.silabs.ss.platform.projectType=makefile
project.target.device=$DEVICE
EOF

# ------------------------------------------------------------------------------
# Link to your real source tree
# ------------------------------------------------------------------------------
ln -sf $SRC_ROOT/app $PROJECT_DIR/app
ln -sf $SRC_ROOT/platform $PROJECT_DIR/platform
ln -sf $SRC_ROOT/drivers $PROJECT_DIR/drivers
ln -sf $SRC_ROOT/wsun $PROJECT_DIR/wsun
ln -sf $SRC_ROOT/common $PROJECT_DIR/common
ln -sf $SRC_ROOT/boards $PROJECT_DIR/boards
ln -sf $SRC_ROOT/Makefile $PROJECT_DIR/Makefile
ln -sf $SRC_ROOT/ldscripts $PROJECT_DIR/ldscripts

echo "Wrapper project created in: $PROJECT_DIR"
echo "Now import this folder into Simplicity Studio using:"
echo "  File → Import → General → Existing Project into Workspace"
echo "Done!"
