<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body onLoad="window.print()">
<?php
// -------------���X�P�f�檺���---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT outinv.* FROM outinv WHERE (outidate >='$outidate1' and outidate<='$outidate2') ";
	$res = mysql_query($SQLStr);
	
//--------------�p���`���Ƥέ���------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>
<!---�C�L�����^���� ------>
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="596" border="0" align="center" cellspacing="0" cellpadding="0" >
    <tr > 
      <td width="619"  align="left">
<?php
//--------------���ƿ�ܧe�{�γs��---------------
     echo "�Ȥ������b�ڪ�&nbsp;&nbsp; ��&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
	    echo "�Ȥ�s��:".$outicustno." ";
		echo "  <a href=index.php?Select=148&page=$i>$i</a>|";
	}
       echo "��, �@".$total."��&nbsp;&nbsp";
?> 
    </td>
    </tr>
  </table>
  <table width="595" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td width="691"> 
        <table width="593" border="0" align="center" >
		  <tr> 
            <td  align="left" colspan="7"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>    
          <tr> 
		     <td width="63" align="left" ><font size="-1">  
              �P�f���</font>
            </td>                     
            <td width="71" align="left" ><font size="-1">  
             �P�f�渹</font> 
            </td>
            <td width="90" align="left" ><font size="-1"> 
			���~�s��</font> 
            </td>           
            <td width="123" align="left" ><font size="-1"> 
			���~�W��</font>  
            </td>			
			<td width="54" align="left" ><font size="-1"> 
			�ƶq</font> 
            </td> 
			 <td width="75" align="left" ><font size="-1"> 
			 ���</font> 
            </td>  
			 <td width="87" align="left" ><font size="-1">  
              ���B</font></td>    
          </tr>
		  <tr> 
            <td  align="left" colspan="7"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>   		  
	<?php
	
//--------------��ܭ��ƾP�f���Ƨe�{�γs���קﭶ���\��-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);	  
	  $SQLStr="select * from outinv WHERE (outidate >='$outidate1' and outidate<='$outidate2' ) limit $first , 10";
	  $res = mysql_query($SQLStr);
	   while (list($outicode, $outino, $outiprodno, $outidate, $outiremark, $outicustno, $outiprodname, $outiprodqty, $outiunit, $outipric, $outiamt)=mysql_fetch_row($res))		
		{		
//--------------- ����ƪ���Ƨe�{---------------
            echo "<tr border='0'   >";	
			echo "<td align='left'><font size='-1'>" . $outidate . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $outino . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $outiprodno  . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $outiprodname . "</font></td>\n";
			echo "<td align=left''><font size='-1'>" . $outiprodqty . "</font></td>\n";			
			echo "<td align='left'><font size='-1'>" . $outipric . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $outiamt . "</font></td>\n";
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
