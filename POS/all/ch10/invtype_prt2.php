<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body onLoad="window.print()">
<?php
// -------------���X��ܪ����~���O�����---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT product.* FROM product WHERE (prodtype='$prodtype') ";	
	$res = mysql_query($SQLStr);

//--------------�p���`���Ƥέ���------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/30);
?>
<!------�j�M����,�^����----------------------->
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="587" border="0" align="center" cellspacing="0" cellpadding="0" >
    <tr > 
      <td  align="left">
		 <?php
//--------------���ƿ�ܧe�{�γs��---------------
     echo "���~���O���Ӫ�&nbsp;&nbsp;<br><font size='-1'>���~���O�s��:&nbsp;&nbsp;".$prodtype. "&nbsp;&nbsp;��&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=326&page=$i>$i</a>|";
	}
       echo "��, �@".$total."��&nbsp;&nbsp</font>";
?>   
    </td>
    </tr>
  </table>
  <table width="593" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td width="593"> 
        <table width="589" border="0"  align="left">
		  <tr> 
          <td  align="left" colspan="7"> 
            <hr  size="1" color="#000000"  width="100%">
          </td>
		  </tr>
          <tr>                     
            <td width="67" align="left" ><font size="-1">
             ���~�s��</font> 
            </td>
            <td width="83" align="left" ><font size="-1"> 
             ���~�W��</font>
            </td>
            <td width="108" align="left" ><font size="-1"> 
              �W�满��</font>
            </td>
            <td width="90" align="left" ><font size="-1"> 
              ���~����</font>
            </td>
			 <td width="73" align="left" ><font size="-1"> 
              �i��</font>
            </td> 
			<td width="65" align="left" ><font size="-1"> 
              ���</font>
            </td>     
			 <td width="73" align="left" ><font size="-1"> 
              �w�s��</font>
            </td>                  
          </tr>
		    <tr> 
            <td  align="left" colspan="7"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
			</tr>		  
	<?php
//--------------��ܭ��Ʋ��~������Ƨe�{�γs�������\��-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=30*($page - 1);
	  $SQLStr="select * from product WHERE (prodtype='$prodtype') limit $first , 30";
	  $res = mysql_query($SQLStr);	
       while (list($prodno, $prodname, $prodtype, $prodvend, $produnit, $prodipric, $prodspric, $prodsave, $prodpqty, $prodnqty, $prodgrap, $prodsdesp, $proddesp, $prodidate, $prododate)=mysql_fetch_row($res))
		{
//------------��ƦC�L���e�e�{,���~������Ʃ���--------------------------------------------	
            echo "<tr border='0'   >";	
			echo "<td align='left'><font size='-1'>" . $prodno  . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $prodname . "</font></td>\n";
			echo "<td align='left'><font size='-1'>";
			if ($prodsdesp == '') 
		         $prodsdesp="�L�W�满��";	        
			echo  $prodsdesp . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $prodtype . "</font></td>\n";		
			echo "<td align='left'><font size='-1'>" . $prodipric . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $prodspric . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $prodnqty . "</font></td>\n";	
			echo "</tr>";		  	
		}	
?>  
        </table>
      </td>
    </tr>
  </table>    
</form>
</body>
</html>
