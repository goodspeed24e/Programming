<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body onLoad="window.print()">
<?php
// -------------���X�Ҧ���ܪ����~���---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT product.* FROM product WHERE (prodno >='$prodno1' and prodno<='$prodno2') ";	
	$res = mysql_query($SQLStr);

//--------------�p���`���Ƥέ���------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/30);
?>
<!------�j�M����,�^����----------------------->
<form name="form1" method="post" action="../index.php?Select=10">

  <table width="659" border="0"  align="center" cellspacing="0" cellpadding="0" >
<?php  
    echo " <tr > ";
      echo "<td  align='left'>";		
//--------------���ƿ�ܧe�{�γs��---------------
     echo "���~���Ӫ�&nbsp;&nbsp; <br>���~�s��:".$prodno1."��".$prodno2."&nbsp;&nbsp;��&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=326&page=$i>$i</a>|";
	}
       echo "��, �@".$total."��&nbsp;&nbsp";
    echo "</td>";
    echo "</tr>";
?>	
  </table>
<!------�j�M����,�^����----------------------->  
  <table width="659" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td width="647"> 
        <table width="592" border="0" align="left" >
		   <tr> 
            <td  align="left" colspan="7"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>
          <tr>                     
            <td width="69"  align="left"><font size="-1"> 
             ���~�s��</font>
            </td>
            <td width="91"  align="left"><font size="-1">  
             ���~�W��</font>
            </td>
            <td width="76"  align="left"><font size="-1">  
              �W�满��</font>
            </td>
            <td width="73"  align="left"><font size="-1">  
              �t��</font>
            </td>
			 <td width="55" align="left"><font size="-1">  
              �i��</font>
            </td> 
			<td width="85"  align="left"><font size="-1">  
              ���</font>
            </td>     
			 <td width="113" align="left"><font size="-1">  
              �w�s��</font>
            </td>                  
          </tr>	
		   <tr> 
            <td  align="left" colspan="7"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>	  
	<?php
//--------------Ū����ƪ�,�Y���~��ƪ����j�M���Ƥ��e-----------------------------------	
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=30*($page - 1);	  
	  $SQLStr="select * from product WHERE (prodno >='$prodno1' and prodno<='$prodno2') limit $first , 30";
	  $res = mysql_query($SQLStr);	
       while (list($prodno, $prodname, $prodtype, $prodvend, $produnit, $prodipric, $prodspric, $prodsave, $prodpqty, $prodnqty, $prodgrap, $prodsdesp, $proddesp, $prodidate, $prododate)=mysql_fetch_row($res))
		{
//------------��ƦC�L���e�e�{,���~��Ʃ���--------------------------------------------	
            echo "<tr border='0'   >";	
			echo "<td align='left'><font size='-1'>" . $prodno  . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $prodname . "</font></td>\n";
			echo "<td align='left'><font size='-1'>";
			if ($prodsdesp == '') 
		         $prodsdesp="�L�W�满��";	        
			echo  $prodsdesp . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $prodvend . "</font></td>\n";		
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
