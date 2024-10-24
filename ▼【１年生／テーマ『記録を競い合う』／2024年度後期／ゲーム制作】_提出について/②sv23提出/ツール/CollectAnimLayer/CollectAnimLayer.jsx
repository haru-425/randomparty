// ヒストリーのまとめとmain関数の呼び出し
app.activeDocument.suspendHistory("CollectAnimation", "main()");


//============================================================================
function main() {
	//　①　UIの本体となるウィンドウを作る
	var win = new Window("dialog", "Collect Animation");

	win.sText = win.add("statictext",[20,10,450,10+25], "選択中の画像を１枚に並べたレイヤーを作成します")
	win.sText = win.add("statictext",[20,10,450,10+25], "事前にレイヤーを下から順番に並べておき、出力したいレイヤーを選択しておいてください")
	win.slider = win.add("slider",[30,30,350,40],1,1,16);
	win.sText = win.add("statictext",[20,10,360,10+25], "横に画像を並べる数を上記スライドで指定してください。　　横の数："+win.slider.value);
	win.slider.onChange = function ()
	{
		win.slider.value = Math.round(win.slider.value);
		win.sText.text = "横に画像を並べる数を上記スライドで指定してください。　　横の数："+win.slider.value;
	}

	var planeBtn1 = win.add("Button", undefined, "実行して結合する");
	planeBtn1.onClick=function()
	{
		win.close();
		makeCollectAnimLayer(true, win.slider.value);
	}

	var planeBtn2 = win.add("Button", undefined, "実行して結合しない");
	planeBtn2.onClick=function()
	{
		win.close();
		makeCollectAnimLayer(false, win.slider.value);
	}
	
	//　ウィンドウを表示する
	win.show();
}

function makeCollectAnimLayer(marge, widthCount)
{
	if (app.documents.length)
	{
		var docRef = app.activeDocument;
		if (docRef.layers.length)
		{
			var newDoc;
			var newLayer;
			
			// 選択されているレイヤーを取得する
			var selected = getSelectedLayerInfo();
			if( selected.length > 1 )
			{
				width = app.activeDocument.width;
				height = app.activeDocument.height;
				
				for (var i = 0; i < selected.length; i++)
				{
					// 選択されているレイヤーのIdxを取得する
					var layer = getLayerByIndex(selected[i]);
					
					if( i == 0 )
					{
						newDoc = app.documents.add(width * widthCount, height*Math.ceil(selected.length/widthCount), layer.resolution, "CollectAnimLayer", NewDocumentMode.RGB, DocumentFill.TRANSPARENT);
						newLayer = app.activeDocument.activeLayer;						
						app.activeDocument = docRef;
					}
				
					var nowLayer = layer.duplicate (newDoc);
					app.activeDocument = newDoc;

					nowLayer.translate(width*( i % widthCount ), height * parseInt( i / widthCount ));
					app.activeDocument = docRef;
				}
			
				app.activeDocument = newDoc;
				if(marge)
				{
					newDoc.mergeVisibleLayers();
				}
				else
				{
					newLayer.remove();
				}
			}
			else
			{
				alert("二つ以上のレイヤーを選択してください");
			}
		}
	}
}

function getSelectedLayerInfo()
{
	var selectedLayers = new Array;

	var ref = new ActionReference();
	ref.putEnumerated(charIDToTypeID("Dcmn"), charIDToTypeID("Ordn"), charIDToTypeID("Trgt"));

	var desc = executeActionGet(ref);
	if (desc.hasKey(stringIDToTypeID('targetLayers')))
	{
		desc = desc.getList(stringIDToTypeID('targetLayers'));

		var c = desc.count
		var selectedLayers = new Array();

		for (var i = 0; i < c; i++)
		{
			try {
				activeDocument.backgroundLayer;
				selectedLayers.push(desc.getReference(i).getIndex());
			} catch (e) {
				selectedLayers.push(desc.getReference(i).getIndex() + 1);
			}
		}
	}
	else
	{
		var ref = new ActionReference();
		ref.putProperty(charIDToTypeID("Prpr"), charIDToTypeID("ItmI"));
		ref.putEnumerated(charIDToTypeID("Lyr "), charIDToTypeID("Ordn"), charIDToTypeID("Trgt"));

		try {
			activeDocument.backgroundLayer;
			selectedLayers.push(executeActionGet(ref).getInteger(charIDToTypeID("ItmI")) - 1);
		} catch (e) {
			selectedLayers.push(executeActionGet(ref).getInteger(charIDToTypeID("ItmI")));
		}

		var vis = app.activeDocument.activeLayer.visible;
		if (vis == true) app.activeDocument.activeLayer.visible = false;

		var desc9 = new ActionDescriptor();
		var list9 = new ActionList();
		var ref9 = new ActionReference();

		ref9.putEnumerated(charIDToTypeID('Lyr '), charIDToTypeID('Ordn'), charIDToTypeID('Trgt'));
		list9.putReference(ref9);
		desc9.putList(charIDToTypeID('null'), list9);
		executeAction(charIDToTypeID('Shw '), desc9, DialogModes.NO);

		if (app.activeDocument.activeLayer.visible == false) selectedLayers.shift();

		app.activeDocument.activeLayer.visible = vis;
	}

	return selectedLayers;
}


function getLayerByIndex(idx)
{
	if (idx == 0) return;

	if (idx.length != undefined)
    {
		idx = idx[0];
	}

	// execute selection
	var desc = new ActionDescriptor();
	var ref = new ActionReference();

	ref.putIndex(charIDToTypeID('Lyr '), idx);
	desc.putReference(charIDToTypeID('null'), ref);
	executeAction(charIDToTypeID('slct'), desc, DialogModes.NO);

	return app.activeDocument.activeLayer;
}