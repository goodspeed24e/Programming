<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php
// -------------���X�Ҧ��P�f�檺���---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT * FROM outinv";
	$res = mysql_query($SQLStr);
//--------------�p���`���Ƥέ���------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>

<form name="form1" method="post" action="outinv/outinvout_mod2.php">

  <table width="782" border="1" align="center" cellspacing="0" cellpadding="0" >
    <tr bgcolor="#99CCFF"> 
      <td align="center">
	 <?php
//--------------���ƿ�ܧe�{�γs��---------------
     echo "�ק�P�f����&nbsp;&nbsp; ��&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=402&page=$i>$i</a>|";
	}
       echo "��, �@".$total."��&nbsp;&nbsp";
?> 
    </td>
    </tr>
  </table>
  <table width="782" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td> 
        <table width="782" border="1" align="center"  bgcolor="#FFFFFF">
          <tr>                     
            <td bgcolor="#99CCFF" align="center"> 
             �P�f�渹
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              ���~�s��
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              ���~�W��
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              �P�f���
            </td>             
          </tr>
<?php
//--------------��ܭ��ƾP�f���Ƨe�{�γs���קﭶ���\��-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
	  $SQLStr="select * from outinv order by outino,outiprodno  limit $first , 10";
	  $res = mysql_query($SQLStr);
	   while (list($outicode, $outino, $outiprodno, $outidate, $outiremark, $outicustno, $outiprodname, $outiprodqty, $outiunit, $outipric, $outiamt)=mysql_fetch_row($res))
		{
//---------------- ����P�f��ƪ���ƨçe�{--------------------
            echo "<tr border='0'   bgcolor='#ffffff'>";	
			echo "<td align='center'>" . $outino  . "</td>\n";
			echo "<td align='center'><a href='outinv/outinvout_mod2.php?outino=" . $outino . "&outiprodno=" . $outiprodno . "'>" . $outiprodno . "</a></td>\n";
			echo "<td align='center'>";
			if ($outiprodname == '') 
		         $outiprodname="�L���~�W��";	        
			echo  $outiprodname . "</td>\n";
			echo "<td align='center'>" . $outidate . "</td>\n";			
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
