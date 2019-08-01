--Objects can be added with the formats:
--Create("assetType", posX, posY, posZ)
--Create("assetType", posX, posY, posZ, rotX, rotY, rotZ)
--Create("assetType", posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ);
--Using -9999 in the posX or posZ position will set posX or posZ to the center of the terrain
--Using -9999 in the posY position will set posY to Terrain::GetHeightat(posX, posZ)


--Player must always be created before any objects with AI
Create("Player", 3428, -9999, 3341, 0, 50, 0);

waterScaleX, waterScaleY, waterScaleZ = 10000, 10000, 1;
Create("Water", -9999, 750, -9999, -90, 0, 0, waterScaleX, waterScaleY, waterScaleZ);


--Crates next to ship
--right row
Create("Crate", 2800, -9999, 6060);
Create("Crate", 2800, -9999, 6000);
Create("Crate", 2800, -9999, 5940);
Create("Crate", 2800, -9999, 5880);

--left row
Create("Crate", 2860, -9999, 6060);
Create("Crate", 2860, -9999, 6000);
Create("Crate", 2860, -9999, 5940);
Create("Crate", 2860, -9999, 5880);


Create("Ship", 2470, -9999, 5971);

Create("Cabin", 4690, -9999, 3600, 0, 180, 0);
Create("Barrel", 4480, -9999, 3782);
Create("Barrel", 4540, -9999, 3782);
Create("Barrel", 4505, -9999, 3831);
Create("PumpkinBunch", 4470, -9999, 3370);
Create("PumpkinBunch", 4730, -9999, 3370);

Create("Cabin", 2771, -9999, 2272, 0, 300, 0);
Create("Cabin", 2895, -9999, 3954, 0, 20, 0);

Create("Hive", 4800, -9999, 7600);
Create("Hive", 8200, -9999, 6500);
Create("Hive", 13510, -9999, 7626);


Create("Tree", 9100, -9999, 8000);
Create("Tree", 10500, -9999, 5500);
Create("Tree", 8760, -9999, 4600);
Create("Tree", 8000, -9999, 4350);


--Farm-ish area
Create("Tree", 9334.88, -9999, 5430.89);
Create("Tree", 8631.7, -9999, 5523.17);
Create("Tree", 8482.53, -9999, 4968.06);

--Trees around cabins
--Create("Tree", 4805, -9999, 3032);
--Create("Tree", 4426, -9999, 4362);
--Create("Tree", 3947, -9999, 4795);
--Create("Tree", 3320, -9999, 4782);
--Create("Tree", 2187, -9999, 3924);
--Create("Tree", 2170, -9999, 3340);
--Create("Tree", 2268, -9999, 2652);
