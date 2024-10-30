import QtQuick 2.15
import QtQuick.Window 2.12
import QtPositioning 5.15
import QtLocation 5.15

Rectangle{
    id:window
    width: 800
    height: 600


    Item {
       id:coord
       property double latitude:0
       property double longitude:0
       objectName:"coord"
       onLatitudeChanged: {
           if (label.latitude !== coord.latitude)
            label.latitude = coord.latitude
       }
       onLongitudeChanged: {
           if (label.longitude !== coord.longtiude)
            label.longitude = coord.longitude
       }

    }
    Item {
       id:temp
       property double latitude:0
       property double longitude:0
       objectName:"temp"
       function getCoords(){
           var lat = temp.latitude;
           var longi = temp.longitude;
           return lat + "," + longi;
       }
       function applyNewLat(lati) {
           if (coord.latitude !== lati)
           coord.latitude = lati
        }
       function applyNewLong(longi) {
           if(coord.longitude !== longi)
           coord.longitude = longi
        }
    }
    Item{
        anchors.fill: parent

        Map {
            id: map
            objectName:"map"
            anchors.fill: parent
            plugin :Plugin {
                name: 'osm'
                PluginParameter {
                    name: 'osm.mapping.geocode'
                    value: true
                }
            }
            property double clat:0
            property double clong:0
            center: QtPositioning.coordinate(map.clat,map.clong)
            zoomLevel: 5;

            Rectangle {
                id: centerBtn
                color: '#2b3856'
                border.color: 'grey'
                border.width: 3
                width: 120; height: 40

                anchors.top: parent.top
                anchors.right: parent.right
                Text{
                    id: buttonLabel
                    color: 'yellow'
                    anchors.centerIn: parent
                    font.pointSize: 12
                    text: 'Re-Center'
                }
                MouseArea {
                       anchors.fill: parent
                       onClicked: { map.center= QtPositioning.coordinate(label.latitude,label.longitude)}
                }
            }
            Rectangle {
                id: refreshBtn
                color: '#2b3856'
                border.color: 'grey'
                border.width: 3
                width: 120; height: 40
                x:parent.width -120
                y:centerBtn.height-5
                Text{
                    id: refreshLabel
                    color: 'yellow'
                    anchors.centerIn: parent
                    font.pointSize: 12
                    text: 'Refresh'
                }
                MouseArea {
                       anchors.fill: parent
                       onClicked: { map.center= QtPositioning.coordinate(label.latitude,label.longitude)
                           parametric.positMap()}
                }
            }

            MapQuickItem {
                id: marker
                coordinate: QtPositioning.coordinate(coord.latitude,coord.longitude)
                property double mlatitude: 0
                property double mlongitude: 0

                onCoordinateChanged: {
                    mlatitude= marker.coordinate.latitude
                    mlongitude= marker.coordinate.longitude
                }

                anchorPoint.x: image.width/2
                anchorPoint.y: image.height/2

                sourceItem: Image {
                    id: image
                    source: "marker.png"
                    width:30
                    height:46.2
                }

                MouseArea {
                     drag.target: marker
                     width: parent.width
                     height: parent.height
                     cursorShape: drag.active ? Qt.ClosedHandCursor : Qt.OpenHandCursor
                     anchors.fill: parent
                }
                Drag.active: true

                onMlatitudeChanged: { label.latitude = marker.mlatitude }
                onMlongitudeChanged: { label.longitude = marker.mlongitude }


            }
            Text {
                id: label
                anchors.fill:parent
                anchors.verticalCenter: parent.verticalCenter
                text: ""
                font.pointSize: 12
                width:800
                height:50
                //color: "blue"
                property double latitude:0
                property int lat1: 0
                property int lat2: 0
                property int lat3: 0
                onLatitudeChanged: {
                    lat1= latitude
                    lat2= Math.abs((latitude%1) * 60)
                    lat3= Math.abs(Math.round(((((latitude%1) * 60)%1) *60)*10000)/10000)
                    text = lat1 + ":" + lat2 + ":" + lat3 + " , " + long1 + ":" + long2 + ":" + long3
                    if (temp.latitude !== label.latitude)   temp.latitude = label.latitude
                }

                property double longitude:0
                property int long1: 0
                property int long2: 0
                property int long3: 0
                onLongitudeChanged: {
                    long1= longitude
                    long2= Math.abs((longitude%1) * 60)
                    long3= Math.abs(Math.round(((((longitude%1) * 60)%1) *60)*10000)/10000)
                    text = lat1 + ":" + lat2 + ":" + lat3 + " , " + long1 + ":" + long2 + ":" + long3
                    if (temp.longitude !== label.longtiude)   temp.longitude = label.longitude
                }

                onTextChanged: {
                    parametric.applyNewPositCoords([lat1,lat2,lat3], [long1,long2,long3])
                }
            }
        }
    }
}
