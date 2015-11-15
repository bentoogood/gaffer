import IECore
import GafferUI
import GafferScene
import GafferSceneUI
import os
scriptNode = script
scriptWindow = GafferUI.ScriptWindow.acquire( script )
layout = eval( "GafferUI.CompoundEditor( scriptNode, children = ( GafferUI.SplitContainer.Orientation.Vertical, 0.956410, ( ( GafferUI.SplitContainer.Orientation.Horizontal, 0.700168, ( ( GafferUI.SplitContainer.Orientation.Vertical, 0.479730, ( {'tabs': (GafferUI.Viewer( scriptNode ),), 'tabsVisible': True, 'currentTab': 0, 'pinned': [True]}, {'tabs': (GafferUI.NodeGraph( scriptNode ),), 'tabsVisible': True, 'currentTab': 0, 'pinned': [None]} ) ), ( GafferUI.SplitContainer.Orientation.Vertical, 0.539189, ( {'tabs': (GafferUI.NodeEditor( scriptNode ), GafferSceneUI.SceneInspector( scriptNode )), 'tabsVisible': True, 'currentTab': 0, 'pinned': [False, False]}, {'tabs': (GafferSceneUI.SceneHierarchy( scriptNode ), GafferUI.ScriptEditor( scriptNode )), 'tabsVisible': True, 'currentTab': 0, 'pinned': [False, None]} ) ) ) ), {'tabs': (GafferUI.Timeline( scriptNode ),), 'tabsVisible': False, 'currentTab': 0, 'pinned': [None]} ) ) )" )
scriptWindow.setLayout( layout )
scriptWindow._Widget__qtWidget.resize(900,720)
for nodeName in ['AppleseedRender']:
	script.selection().add( script.descendant( nodeName ) )
script.context()["ui:scene:expandedPaths"] = GafferScene.PathMatcherData( GafferScene.PathMatcher( ['/'] ) )
script.context()["ui:scene:selectedPaths"] = IECore.StringVectorData( [  ] )
##############################################################
## IMAGE SPECIFIC COMMANDS BELOW #############################

# add little nugget to load the Display node into the pinned editor
v = scriptWindow.getLayout().editors(GafferUI.Viewer)[0]
v.getNodeSet().add(script['Display'])

# do a render
with script.context() :
    script['AppleseedRender'].execute()
