# Name:         xxx.py ('xxx' is easy to distinguish from 'wx' :) )
# Purpose:      XML interface classes
# Author:       Roman Rolinsky <rolinsky@mema.ucl.ac.be>
# Created:      22.08.2001
# RCS-ID:       $Id$

from wxPython.wx import *
from wxPython.xrc import *
from xml.dom import minidom
import wxPython.lib.wxpTag

from params import *

# Classes to interface DOM objects
class xxxObject:
    # Default behavior
    hasChildren = false                 # has children elements?
    hasStyle = true                     # almost everyone
    hasName = true                      # has name attribute?
    isSizer = hasChild = false
    # Style parameters (all optional)
    styles = ['fg', 'bg', 'font', 'enabled', 'focused', 'hidden', 'tooltip']
    # Required paremeters: none by default
    required = []
    # Default parameters with default values
    default = {}
    # Parameter types
    paramDict = {}
    # Window styles and extended styles
    winStyles = []
    # Tree icon index
    #image = -1
    # Construct a new xxx object from DOM element
    # parent is parent xxx object (or None if none), element is DOM element object
    def __init__(self, parent, element):
        self.parent = parent
        self.element = element
        self.undo = None
        # Get attributes
        self.className = element.getAttribute('class')
        if self.hasName: self.name = element.getAttribute('name')
        # Set parameters (text element children)
        self.params = {}
        nodes = element.childNodes[:]
        for node in nodes:
            if node.nodeType == minidom.Node.ELEMENT_NODE:
                if node.tagName == 'object':
                    continue            # do nothing for object children here
                if not node.tagName in self.allParams and not node.tagName in self.styles:
                    print 'WARNING: unknown parameter for %s: %s' % \
                          (self.className, node.tagName)
                    continue
                if node.tagName == 'content': # has items
                    # Param value is a list of text nodes
                    l = []
                    nodes = node.childNodes[:]
                    for n in nodes:
                        if n.nodeType == minidom.Node.ELEMENT_NODE:
                            assert n.tagName == 'item', 'bad content content'
                            if not n.hasChildNodes():
                                # If does not have child nodes, create empty text node
                                text = tree.dom.createTextNode('')
                                node.appendChild(text)
                            else:
                                # !!! normalize?
                                text = n.childNodes[0] # first child must be text node
                                assert text.nodeType == minidom.Node.TEXT_NODE
                            l.append(text)
                        else:
                            node.removeChild(n)
                            n.unlink()
                    self.params[node.tagName] = l
                elif node.tagName == 'font': # has children
                    # we read and write all font parameters at once
                    self.params[node.tagName] = xxxFont(self, node)
                else:                   # simple parameter
                    if not node.hasChildNodes():
                        # If does not have child nodes, create empty text node
                        text = tree.dom.createTextNode('')
                        node.appendChild(text)
                    else:
                        text = node.childNodes[0] # first child must be text node
                        assert text.nodeType == minidom.Node.TEXT_NODE
                    self.params[node.tagName] = text
            else:
                # Remove all other nodes
                element.removeChild(node)
                node.unlink()
    # Generate HTML
    def generateHtml(self, prefix=''):
        SetCurrentXXX(self)
        html = '<table cellspacing=0 cellpadding=0><tr><td width=120>\
<font size="+1"><b>%s</b></font></td>' % self.className
        # Has id (name) attribute
        if self.hasName:
            html += """\
<td><wxp module="xxx" class="ParamText" width=150>
<param name="id" value="%d">
<param name="name" value="data_name">
<param name="value" value='("%s")'>
</wxp></td>""" % (-1, self.name)
        html += '</table><p>'
        html += '<table cellspacing=0 cellpadding=0>\n'
        # Add required parameters
        for param in self.allParams:
            # Add checkbox or just text
            if param in self.required:
                html += '<tr><td width=20></td><td width=100>%s: </td>' % param
            else:                       # optional parameter
                html += """\
<tr><td width=20><wxp class="wxCheckBox">
<param name="id" value="%d">
<param name="size" value="(20,-1)">
<param name="name" value="%s">
<param name="label" value=("")>
</wxp></td><td width=100>%s: </td>
""" % (paramIDs[param], prefix + 'check_' + param, param)
            # Add value part
            if self.params.has_key(param):
                if param == 'content':
                    l = []
                    for text in self.params[param]:
                        l.append(str(text.data)) # convert from unicode
                    value = str(l)
                else:
                    value = "('" + self.params[param].data + "')"
            else:
                value = "('')"
            # Get parameter type
            try:
                # Local or overriden type
                typeClass = self.paramDict[param].__name__
            except KeyError:
                try:
                    # Standart type
                    typeClass = paramDict[param].__name__
                except KeyError:
                    # Default
                    typeClass = 'ParamText'
            html += """\
<td><wxp module="xxx" class="%s">
<param name="id" value="%d">
<param name="name" value="%s">
<param name="value" value="%s">
</wxp></td>
""" % (typeClass, -1, prefix + 'data_' + param, value)
        html += '</table>\n'
        return html
    # Returns real tree object
    def treeObject(self):
        if self.hasChild: return self.child
        return self
    # Returns tree image index
    def treeImage(self):
        if self.hasChild: return self.child.treeImage()
        return self.image
    # Class name plus wx name
    def treeName(self):
        if self.hasChild: return self.child.treeName()
        if self.hasName and self.name: return self.className + ' "' + self.name + '"'
        return self.className

################################################################################

class xxxFont(xxxObject):
    allParams = ['size', 'style', 'weight', 'family', 'underlined',
                 'face', 'encoding']
    def __init__(self, parent, element):
        xxxObject.__init__(self, parent, element)
        self.parentNode = element       # required to behave similar to DOM node
        self.data = self.value()
    def updateXML(self, value):
        # `value' is a list of strings corresponding to all parameters
        elem = self.element
        for node in elem.childNodes:
            elem.removeChild(node)
        i = 0
        self.params.clear()
        for param in self.allParams:
            if value[i]:
                fontElem = tree.dom.createElement(param)
                textNode = tree.dom.createTextNode(value[i])
                self.params[param] = textNode
                fontElem.appendChild(textNode)
                elem.appendChild(fontElem)
            i += 1
        # Update data
        self.data = self.value()
    def value(self):
        v = []
        for p in self.allParams:
            try:
                v.append(str(self.params[p].data))
            except KeyError:
                v.append('')
        return v

################################################################################

class xxxContainer(xxxObject):
    hasChildren = true

################################################################################
# Top-level windwos

class xxxPanel(xxxContainer):
    allParams = ['pos', 'size', 'style']
    styles = ['fg', 'bg', 'font', 'enabled', 'focused', 'hidden', 'exstyle',
              'tooltip']
    exStyles = ['wxWS_EX_VALIDATE_RECURSIVELY']

class xxxDialog(xxxContainer):
    allParams = ['title', 'pos', 'size', 'style']
    required = ['title']
    winStyles = ['wxDIALOG_MODAL', 'wxCAPTION', 'wxDEFAULT_DIALOG_STYLE',
              'wxRESIZE_BORDER', 'wxSYSTEM_MENU',  'wxTHICK_FRAME', 'wxSTAY_ON_TOP']
    styles = ['fg', 'bg', 'font', 'enabled', 'focused', 'hidden', 'exstyle',
              'tooltip']
    exStyles = ['wxWS_EX_VALIDATE_RECURSIVELY']

class xxxFrame(xxxContainer):
    allParams = ['title', 'centered', 'pos', 'size', 'style']
    paramDict = {'centered': ParamBool}
    required = ['title']
    winStyles = ['wxDEFAULT_FRAME_STYLE', 'wxICONIZE', 'wxCAPTION', 'wxMINIMIZE',
              'wxICONIZE', 'wxMINIMIZE_BOX', 'wxMAXIMIZE', 'wxMAXIMIZE_BOX',
              'wxSTAY_ON_TOP', 'wxSYSTEM_MENU', 'wxRESIZE_BORDER',
              'wxFRAME_FLOAT_ON_PARENT', 'wxFRAME_TOOL_WINDOW']
    styles = ['fg', 'bg', 'font', 'enabled', 'focused', 'hidden', 'exstyle',
              'tooltip']
    exStyles = ['wxWS_EX_VALIDATE_RECURSIVELY']

################################################################################
# Controls

class xxxStaticText(xxxObject):
    allParams = ['label', 'pos', 'size', 'style']
    required = ['label']
    winStyles = ['wxALIGN_LEFT', 'wxALIGN_RIGHT', 'wxALIGN_CENTRE', 'wxST_NO_AUTORESIZE']

class xxxStaticLine(xxxObject):
    allParams = ['pos', 'size', 'style']
    winStyles = ['wxLI_HORIZONTAL', 'wxLI_VERTICAL']

class xxxTextCtrl(xxxObject):
    allParams = ['value', 'pos', 'size', 'style']
    winStyles = ['wxTE_PROCESS_ENTER', 'wxTE_PROCESS_TAB', 'wxTE_MULTILINE',
              'wxTE_PASSWORD', 'wxTE_READONLY']

class xxxChoice(xxxObject):
    allParams = ['content', 'selection', 'pos', 'size', 'style']
    required = ['content']

class xxxSlider(xxxObject):
    allParams = ['value', 'min', 'max', 'pos', 'size', 'style',
                 'tickfreq', 'pagesize', 'linesize', 'thumb', 'tick',
                 'selmin', 'selmax']
    paramDict = {'value': ParamInt, 'tickfreq': ParamInt, 'pagesize': ParamInt,
                 'linesize': ParamInt, 'thumb': ParamInt, 'thumb': ParamInt,
                 'tick': ParamInt, 'selmin': ParamInt, 'selmax': ParamInt}
    required = ['value', 'min', 'max']
    winStyles = ['wxSL_HORIZONTAL', 'wxSL_VERTICAL', 'wxSL_AUTOTICKS', 'wxSL_LABELS',
              'wxSL_LEFT', 'wxSL_RIGHT', 'wxSL_TOP', 'wxSL_SELRANGE']

class xxxGauge(xxxObject):
    allParams = ['range', 'pos', 'size', 'style', 'value', 'shadow', 'bezel']
    paramDict = {'range': ParamInt, 'value': ParamInt,
                 'shadow': ParamInt, 'bezel': ParamInt}
    winStyles = ['wxGA_HORIZONTAL', 'wxGA_VERTICAL', 'wxGA_PROGRESSBAR', 'wxGA_SMOOTH']

class xxxScrollBar(xxxObject):
    allParams = ['pos', 'size', 'style', 'value', 'thumbsize', 'range', 'pagesize']
    paramDict = {'value': ParamInt, 'range': ParamInt, 'thumbsize': ParamInt,
                 'pagesize': ParamInt}
    winStyles = ['wxSB_HORIZONTAL', 'wxSB_VERTICAL']

class xxxListCtrl(xxxObject):
    allParams = ['pos', 'size', 'style']
    winStyles = ['wxLC_LIST', 'wxLC_REPORT', 'wxLC_ICON', 'wxLC_SMALL_ICON',
              'wxLC_ALIGN_TOP', 'wxLC_ALIGN_LEFT', 'wxLC_AUTOARRANGE',
              'wxLC_USER_TEXT', 'wxLC_EDIT_LABELS', 'wxLC_NO_HEADER',
              'wxLC_SINGLE_SEL', 'wxLC_SORT_ASCENDING', 'wxLC_SORT_DESCENDING']

# !!! temporary
xxxCheckList = xxxListCtrl

class xxxTreeCtrl(xxxObject):
    allParams = ['pos', 'size', 'style']
    winStyles = ['wxTR_HAS_BUTTONS', 'wxTR_NO_LINES', 'wxTR_LINES_AT_ROOT',
              'wxTR_EDIT_LABELS', 'wxTR_MULTIPLE']

class xxxHtmlWindow(xxxObject):
    allParams = ['pos', 'size', 'style', 'borders', 'url', 'htmlcode']
    paramDict = {'borders': ParamInt}
    winStyles = ['wxHW_SCROLLBAR_NEVER', 'wxHW_SCROLLBAR_AUTO']

class xxxCalendar(xxxObject):
    allParams = ['pos', 'size', 'style']

class xxxNotebook(xxxContainer):
    allParams = ['usenotebooksizer', 'pos', 'size', 'style']
    paramDict = {'usenotebooksizer': ParamBool}
    winStyles = ['wxNB_FIXEDWIDTH', 'wxNB_LEFT', 'wxNB_RIGHT', 'wxNB_BOTTOM']

################################################################################
# Buttons

class xxxButton(xxxObject):
    allParams = ['label', 'default', 'pos', 'size', 'style']
    paramDict = {'default': ParamBool}
    required = ['label']
    winStyles = ['wxBU_LEFT', 'wxBU_TOP', 'wxBU_RIGHT', 'wxBU_BOTTOM']

class xxxBitmapButton(xxxObject):
    allParams = ['bitmap', 'selected', 'focus', 'disabled', 'default',
                 'pos', 'size', 'style']
    required = ['bitmap']
    winStyles = ['wxBU_LEFT', 'wxBU_TOP', 'wxBU_RIGHT', 'wxBU_BOTTOM']

class xxxRadioButton(xxxObject):
    allParams = ['label', 'value', 'pos', 'size', 'style']
    paramDict = {'value': ParamBool}
    required = ['label']
    winStyles = ['wxRB_GROUP']

class xxxSpinButton(xxxObject):
    allParams = ['pos', 'size', 'style']
    winStyles = ['wxSP_HORIZONTAL', 'wxSP_VERTICAL', 'wxSP_ARROW_KEYS', 'wxSP_WRAP']

################################################################################
# Boxes

class xxxStaticBox(xxxObject):
    allParams = ['label', 'pos', 'size', 'style']
    required = ['label']

class xxxRadioBox(xxxObject):
    allParams = ['label', 'content', 'selection', 'dimension', 'pos', 'size', 'style']
    paramDict = {'dimension': ParamInt}
    required = ['label', 'content']
    winStyles = ['wxRA_SPECIFY_ROWS', 'wxRA_SPECIFY_COLS']

class xxxCheckBox(xxxObject):
    allParams = ['label', 'pos', 'size', 'style']
    required = ['label']

class xxxComboBox(xxxObject):
    allParams = ['content', 'selection', 'value', 'pos', 'size', 'style']
    required = ['content']
    winStyles = ['wxCB_SIMPLE', 'wxCB_DROPDOWN', 'wxCB_READONLY', 'wxCB_DROPDOWN',
              'wxCB_SORT']

class xxxListBox(xxxObject):
    allParams = ['content', 'selection', 'pos', 'size', 'style']
    required = ['content']
    winStyles = ['wxLB_SINGLE', 'wxLB_MULTIPLE', 'wxLB_EXTENDED', 'wxLB_HSCROLL',
              'wxLB_ALWAYS_SB', 'wxLB_NEEDED_SB', 'wxLB_SORT']

################################################################################
# Sizers

class xxxSizer(xxxContainer):
    hasName = hasStyle = false
    paramDict = {'orient': ParamOrient}
    isSizer = true

class xxxBoxSizer(xxxSizer):
    allParams = ['orient']
    required = ['orient']
    default = {'orient': 'wxVERTICAL'}
    # Tree icon depends on orientation
    def treeImage(self):
        if self.params['orient'].data == 'wxHORIZONTAL': return self.imageH
        else: return self.imageV

class xxxStaticBoxSizer(xxxBoxSizer):
    allParams = ['label', 'orient']
    required = ['label', 'orient']
    default = {'orient': 'wxVERTICAL'}

class xxxGridSizer(xxxSizer):
    allParams = ['cols', 'rows', 'vgap', 'hgap']
    required = ['cols']
    default = {'cols': '2', 'rows': '2'}

class xxxFlexGridSizer(xxxGridSizer):
    pass

# Container with only one child.
# Not shown in tree.
class xxxChildContainer(xxxObject):
    hasName = hasStyle = false
    hasChild = true
    def __init__(self, parent, element):
        xxxObject.__init__(self, parent, element)
        # Must have one child with 'object' tag, but we don't check it
        nodes = element.childNodes[:]   # create copy
        for node in nodes:
            if node.nodeType == minidom.Node.ELEMENT_NODE:
                if node.tagName == 'object':
                    # Create new xxx object for child node
                    self.child = MakeXXXFromDOM(self, node)
                    self.child.parent = parent
                    # Copy hasChildren and isSizer attributes
                    self.hasChildren = self.child.hasChildren
                    self.isSizer = self.child.isSizer
                    return              # success
            else:
                element.removeChild(node)
                node.unlink()
        assert 0, 'no child found'
    def generateHtml(self):
        return xxxObject.generateHtml(self, '_') + '<hr>\n' + \
               self.child.generateHtml()

class xxxSizerItem(xxxChildContainer):
    allParams = ['option', 'flag', 'border']
    paramDict = {'option': ParamInt}
    def __init__(self, parent, element):
        xxxChildContainer.__init__(self, parent, element)
        # Remove pos parameter - unnecessary for sizeritems
        if 'pos' in self.child.allParams:
            self.child.allParams = self.child.allParams[:]
            self.child.allParams.remove('pos')

class xxxNotebookPage(xxxChildContainer):
    allParams = ['label', 'selected']
    paramDict = {'selected': ParamBool}
    required = ['label']
    def __init__(self, parent, element):
        xxxChildContainer.__init__(self, parent, element)
        # pos and size dont matter for notebookpages
        if 'pos' in self.child.allParams:
            self.child.allParams = self.child.allParams[:]
            self.child.allParams.remove('pos')
        if 'size' in self.child.allParams:
            self.child.allParams = self.child.allParams[:]
            self.child.allParams.remove('size')

class xxxSpacer(xxxObject):
    hasName = hasStyle = false
    allParams = ['size', 'option', 'flag', 'border']
    paramDict = {'option': ParamInt}
    default = {'size': '0,0'}

class xxxMenuBar(xxxContainer):
    allParams = []

class xxxMenu(xxxContainer):
    allParams = ['label']
    default = {'label': ''}

class xxxMenuItem(xxxObject):
    allParams = ['checkable', 'label', 'accel', 'help']
    default = {'label': ''}

class xxxSeparator(xxxObject):
    hasName = hasStyle = false
    allParams = []

################################################################################

xxxDict = {
    'wxPanel': xxxPanel,
    'wxDialog': xxxDialog,
    'wxFrame': xxxFrame,
    
    'wxButton': xxxButton,
    'wxBitmapButton': xxxBitmapButton,
    'wxRadioButton': xxxRadioButton,
    'wxSpinButton': xxxSpinButton,

    'wxStaticBox': xxxStaticBox,
    'wxRadioBox': xxxRadioBox,
    'wxComboBox': xxxComboBox,
    'wxCheckBox': xxxCheckBox,
    'wxListBox': xxxListBox,

    'wxStaticText': xxxStaticText,
    'wxStaticLine': xxxStaticLine,
    'wxTextCtrl': xxxTextCtrl,
    'wxChoice': xxxChoice,
    'wxSlider': xxxSlider,
    'wxGauge': xxxGauge,
    'wxScrollBar': xxxScrollBar,
    'wxTreeCtrl': xxxTreeCtrl,
    'wxListCtrl': xxxListCtrl,
    'wxCheckList': xxxCheckList,
    'wxNotebook': xxxNotebook,
    'notebookpage': xxxNotebookPage,
    'wxHtmlWindow': xxxHtmlWindow,
    'wxCalendar': xxxCalendar,
    
    'wxBoxSizer': xxxBoxSizer,
    'wxStaticBoxSizer': xxxStaticBoxSizer,
    'wxGridSizer': xxxGridSizer,
    'wxFlexGridSizer': xxxFlexGridSizer,
    'sizeritem': xxxSizerItem,
    'spacer': xxxSpacer,

    'wxMenuBar': xxxMenuBar,
    'wxMenu': xxxMenu,
    'wxMenuItem': xxxMenuItem,
    'separator': xxxSeparator,
    }

# Create IDs for all parameters of all classes
paramIDs = {'fg': wxNewId(), 'bg': wxNewId(), 'exstyle': wxNewId(), 'font': wxNewId(),
            'enabled': wxNewId(), 'focused': wxNewId(), 'hidden': wxNewId(),
            'tooltip': wxNewId()
            }
for cl in xxxDict.values():
    for param in cl.allParams + cl.paramDict.keys():
        if not paramIDs.has_key(param):
            paramIDs[param] = wxNewId()

################################################################################
# Helper functions

# Test for object elements
def IsObject(node):
    return node.nodeType == minidom.Node.ELEMENT_NODE and node.tagName == 'object'

# Make XXX object from some DOM object, selecting correct class
def MakeXXXFromDOM(parent, element):
    return xxxDict[element.getAttribute('class')](parent, element)

# Make empty DOM element
def MakeEmptyDOM(className): 
    elem = tree.dom.createElement('object')
    elem.setAttribute('class', className)
    # Set required and default parameters
    xxxClass = xxxDict[className]
    defaultNotRequired = filter(lambda x, l=xxxClass.required: x not in l,
                                xxxClass.default.keys())
    for param in xxxClass.required + defaultNotRequired:
        textElem = tree.dom.createElement(param)
        try:
            textNode = tree.dom.createTextNode(xxxClass.default[param])
        except KeyError:
            textNode = tree.dom.createTextNode('')
        textElem.appendChild(textNode)
        elem.appendChild(textElem)
    return elem

# Make empty XXX object
def MakeEmptyXXX(parent, className):
    # Make corresponding DOM object first
    elem = MakeEmptyDOM(className)
    # If parent is a sizer, we should create sizeritem object, except for spacers
    if parent:
        if parent.isSizer and className != 'spacer':
            sizerItemElem = MakeEmptyDOM('sizeritem')
            sizerItemElem.appendChild(elem)
            elem = sizerItemElem
        elif isinstance(parent, xxxNotebook):
            pageElem = MakeEmptyDOM('notebookpage')
            pageElem.appendChild(elem)
            elem = pageElem
    # Now just make object
    return MakeXXXFromDOM(parent, elem)

